/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 * 
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "PythonMergerCreator.h"

// hoot
#include <hoot/core/conflate/merging/MarkForReviewMerger.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/util/StringUtils.h>

#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/conflate/matching/PythonMatch.h>
#include <hoot/py/conflate/merging/PythonMerger.h>
#include <hoot/py/conflate/matching/PythonCreatorDescription.h>

// pybind11
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

using namespace std;

namespace hoot
{

HOOT_FACTORY_REGISTER(MergerCreator, PythonMergerCreator)

void init_PythonMergerCreator(py::module_& m)
{
    auto wrapme = py::class_<PythonMergerCreator, shared_ptr<PythonMergerCreator> >(m,
        "PythonMergerCreator")
      .def(py::init([]() { return make_shared<PythonMergerCreator>(); }))
      .def_static("clear", &PythonMergerCreator::clear)
      .def_static("registerCreator", &PythonMergerCreator::registerCreator)
      .def("setArguments", [](PythonMergerCreator& self, vector<QString> strs) {
        LOG_VARW(strs);
        self.setArguments(QStringList(strs.begin(), strs.end()));
      })
    ;
    hoot::PyBindModule::remapNames(wrapme);

    // call this when the module is unloaded to avoid holding on to python points and causing a
    // deadlock.
    m.add_object("__cleanup_PythonMergerCreator",
      py::capsule([]() { PythonMergerCreator::clear(); }));
}

REGISTER_PYHOOT_SUBMODULE(init_PythonMergerCreator)

QList<PythonCreatorDescriptionPtr> PythonMergerCreator::_creators;

PythonMergerCreator::PythonMergerCreator()
{
  LOG_TRACE("PythonMergerCreator")
}

void PythonMergerCreator::clear()
{
  for (auto desc : _creators)
  {
    desc->clear();
  }
  _creators.clear();
}

bool PythonMergerCreator::createMergers(const MatchSet& matches, vector<MergerPtr>& mergers) const
{
  LOG_TRACE(
    "Creating merger group with " << className() << " for " <<
    StringUtils::formatLargeNumber(matches.size()) << " match(es)...");

  bool result = false;
  assert(matches.size() > 0);

  set<pair<ElementId, ElementId>> eids;

  QStringList matchType;

  // Go through all the matches.
  for (MatchSet::const_iterator it = matches.begin(); it != matches.end(); ++it)
  {
    ConstMatchPtr match = *it;;
    std::shared_ptr<const PythonMatch> scriptMatch = dynamic_pointer_cast<const PythonMatch>(match);
    // Check to make sure all the input matches are script matches.
    if (scriptMatch == nullptr)
    {
      // Return an empty result.
      LOG_TRACE("Match invalid; skipping merge: " << match->toString());
      return false;
    }
    // Add all the element to element pairs to a set.
    else
    {
      set<pair<ElementId, ElementId>> s = scriptMatch->getMatchPairs();
      eids.insert(s.begin(), s.end());
      if (matchType.contains(scriptMatch->getName()) == false)
      {
        matchType.append(scriptMatch->getName());
      }
    }
  }
  LOG_VART(eids);

  std::shared_ptr<PythonMerger> scriptMerger = std::make_shared<PythonMerger>(_pyInfo, eids);
  scriptMerger->setMatchType(matchType.join(";"));
  // merge set can handle an arbitrarily large number of elements
  if (_pyInfo->getMergeSet() != nullptr)
  {
    // Only add the merger if there are elements to merge.
    if (eids.size() >= 1)
    {
      mergers.push_back(scriptMerger);
      result = true;
    }
  }
  // if the user only has mergePair implemented
  else
  {
    // if there is one pair of elements, we can handle that
    if (eids.size() == 1)
    {
      mergers.push_back(scriptMerger);
      result = true;
    }
    // multiple pairs of matches can't be handled w/ merge pair, automagically mark it as needing
    // review.
    else if (eids.size() > 1)
    { 
      LOG_TRACE("Overlapping matches:\n" << eids << "\nmatch types: " << matchType.join(";"));
      mergers.push_back(
        std::make_shared<MarkForReviewMerger>(
          eids, "Overlapping matches", matchType.join(";"), 1.0));
      result = true;
    }
  }

  LOG_TRACE(
    "Created " << StringUtils::formatLargeNumber(mergers.size()) <<  " merger(s) for group.");
  return result;
}

vector<CreatorDescription> PythonMergerCreator::getAllCreators() const
{
  LOG_TRACE("getAllCreators");
  CreatorDescription d;
  d.setClassName(className());
  d.setDescription("Generates mergers used in Generic Conflation");
  d.setExperimental(false);
  vector<CreatorDescription> result;
  result.push_back(d);
  return result;
}

bool PythonMergerCreator::isConflicting(
  const ConstOsmMapPtr& map, ConstMatchPtr m1, ConstMatchPtr m2,
  const QHash<QString, ConstMatchPtr>& matches) const
{
  LOG_TRACE("isConflicting");
  const PythonMatch* sm1 = dynamic_cast<const PythonMatch*>(m1.get());
  const PythonMatch* sm2 = dynamic_cast<const PythonMatch*>(m2.get());

  bool result = false;
  if (sm1 && sm2)
  {
    result = m1->isConflicting(m2, map, matches);
  }

  return result;
}

void PythonMergerCreator::setArguments(QStringList args)
{
  LOG_TRACE("setArguments");
  if (args.size() != 1)
  {
    throw HootException("The PythonMergerCreator takes exactly one argument (className).");
  }

  QString className = args[0];

  _pyInfo = nullptr;
  for (shared_ptr<PythonCreatorDescription> desc : _creators)
  {
    LOG_TRACE(desc->getDescription()->getClassName());
    if (desc->getDescription()->getClassName() == className)
    {
      _pyInfo = desc;
    }
  }

  if (_pyInfo == nullptr)
  {
    throw HootException("invalid creator class name: " + className);
  }

  LOG_DEBUG("Set arguments for: " << PythonMergerCreator::className() << " - className: " <<
    className);
}

}
