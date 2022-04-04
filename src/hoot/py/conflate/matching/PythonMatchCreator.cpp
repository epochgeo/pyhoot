/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 * 
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "PythonMatchCreator.h"

// hoot
#include <hoot/core/conflate/matching/MatchThreshold.h>
#include <hoot/core/conflate/matching/MatchType.h>
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/io/OsmJsonWriter.h>
#include <hoot/core/info/CreatorDescription.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/util/StringUtils.h>

// pybind11
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/conflate/matching/PythonCreatorDescription.h>
#include <hoot/py/conflate/matching/PythonMatchCreator.h>
#include <hoot/py/conflate/matching/PythonMatchVisitor.h>

// Qt
#include <qnumeric.h>
#include <QStringBuilder>
#include <QElapsedTimer>

// Standard
#include <functional>
#include <cmath>

using namespace geos::geom;
using namespace std;
using namespace Tgs;

namespace py = pybind11;

namespace hoot
{

HOOT_FACTORY_REGISTER(MatchCreator, PythonMatchCreator)

void init_PythonMatchCreator(py::module_& m)
{
    auto matchCreator = py::class_<MatchCreator, shared_ptr<MatchCreator> >(m, "MatchCreator");

    auto wrapme = py::class_<PythonMatchCreator, shared_ptr<PythonMatchCreator> >(m,
        "PythonMatchCreator", matchCreator)
      .def(py::init([]() { return make_shared<PythonMatchCreator>(); }))
      .def_static("clear", &PythonMatchCreator::clear)
      .def("init", &PythonMatchCreator::init)
      .def("getCreatorByName", &PythonMatchCreator::getCreatorByName,
"getCreatorByName returns the creator python info for a specified name.")
      .def("getName", &PythonMatchCreator::getName)
      .def_static("registerCreator", &PythonMatchCreator::registerCreator)
      .def("setArguments", [](PythonMatchCreator& self, vector<QString> strs) {
        LOG_VARW(strs);
        self.setArguments(QStringList(strs.begin(), strs.end()));
      })
      .def("setName", &PythonMatchCreator::setName)
    ;
    hoot::PyBindModule::remapNames(wrapme);

    // call this when the module is unloaded to avoid holding on to python points and causing a
    // deadlock.
    m.add_object("__cleanup_PythonMatchCreator",
      py::capsule([]() { PythonMatchCreator::clear(); }));
}

REGISTER_PYHOOT_SUBMODULE(init_PythonMatchCreator)

QList< std::shared_ptr<PythonCreatorDescription> > PythonMatchCreator::_creators;

PythonMatchCreator::PythonMatchCreator()
{
}

void PythonMatchCreator::clear()
{
  for (auto desc : _creators)
  {
    desc->clear();
  }
  _creators.clear();
}

void PythonMatchCreator::setConfiguration(const Settings& conf)
{
  ConfigOptions opts(conf);
}

void PythonMatchCreator::init(const ConstOsmMapPtr& map)
{
  LOG_TRACE("init");
  LOG_VAR(OsmJsonWriter().toString(map));
//  if (_creatorInfo && _creatorInfo->getInitFunction())
//  {
//    _creatorInfo->getInitFunction()(map);
//  }
  //_getCachedVisitor(map)->initSearchRadiusInfo();
}

Meters PythonMatchCreator::calculateSearchRadius(
  const ConstOsmMapPtr& map, const ConstElementPtr& e)
{
  return _getCachedVisitor(map)->getSearchRadius(e);
}

void PythonMatchCreator::setArguments(const QStringList& args)
{
  LOG_TRACE("setArguments");
  if (args.size() != 1)
  {
    throw HootException("The PythonMatchCreator takes exactly one argument (className).");
  }

  QString className = args[0];

  _creatorInfo = nullptr;
  for (shared_ptr<PythonCreatorDescription> desc : _creators)
  {
    if (desc->getDescription()->getClassName() == className)
    {
      _creatorInfo = desc;
    }
  }

  if (_creatorInfo == nullptr)
  {
    throw HootException("invalid creator class name: " + className);
  }

  setConfiguration(conf());

  LOG_DEBUG("Set arguments for: " << PythonMatchCreator::className() << " - className: " <<
    className);
}

MatchPtr PythonMatchCreator::createMatch(
  const ConstOsmMapPtr& map, ElementId eid1, ElementId eid2)
{
  // There may be some benefit at some point in caching matches calculated in PythonMatchCreator and
  // accessing that cached information here to avoid extra calls into the JS match script. So far,
  // haven't seen any performance improvement after adding match caching.
  return nullptr;
}

void PythonMatchCreator::createMatches(
  const ConstOsmMapPtr& map, std::vector<ConstMatchPtr>& matches, ConstMatchThresholdPtr threshold)
{
  LOG_TRACE("createMatches");
  assert(_creatorInfo);
  assert(threshold);

  // The parent does some initialization we need.
  MatchCreator::createMatches(map, matches, threshold);

  QElapsedTimer timer;
  timer.start();

  PythonMatchVisitorPtr v = _getCachedVisitor(map);
  v->setResultVector(&matches);
  LOG_VART(v.get());

  // This doesn't work with _candidateDistanceSigma, but right now its set to 1.0 in every script
  // and has no effect on the search radius.
  QString searchRadiusStr;
  const double searchRadius = _creatorInfo->getSearchRadius();
  if (_creatorInfo->getSearchRadiusFunction())
  {
    searchRadiusStr = "within a function calculated search radius";
  }
  else if (searchRadius < 0)
  {
    searchRadiusStr = "within a feature dependent search radius";
  }
  else
  {
    searchRadiusStr =
      "within a search radius of " + QString::number(searchRadius, 'g', 2) + " meters";
  }

  LOG_INFO(
    "Looking for matches with: " << _creatorInfo->getDescription()->getClassName() << " " 
      << searchRadiusStr << "...");
  LOG_VARD(*threshold);
  const int matchesSizeBefore = matches.size();

  QString matchType = CreatorDescription::baseFeatureTypeToString(
    _creatorInfo->getDescription()->getBaseFeatureType());
  LOG_VARD(matchType);
  switch (_creatorInfo->getDescription()->getBaseFeatureType())
  {
    case CreatorDescription::BaseFeatureType::POI:
    case CreatorDescription::BaseFeatureType::Point:
      map->visitNodesRo(*v);
      break;
    case CreatorDescription::BaseFeatureType::Highway:
    case CreatorDescription::BaseFeatureType::Building:
    case CreatorDescription::BaseFeatureType::River:
    case CreatorDescription::BaseFeatureType::Polygon:
    case CreatorDescription::BaseFeatureType::Area:
    case CreatorDescription::BaseFeatureType::Railway:
    case CreatorDescription::BaseFeatureType::PowerLine:
    case CreatorDescription::BaseFeatureType::Line:
      map->visitWaysRo(*v);
      map->visitRelationsRo(*v);
      break;
    case CreatorDescription::BaseFeatureType::Relation:
      map->visitRelationsRo(*v);
      break;
    case CreatorDescription::BaseFeatureType::PoiPolygonPOI:
      map->visitRo(*v);
      break;
    default:
      // visit all geometry types if the script didn't identify its geometry
      LOG_INFO("Unrecognized geometry type, scanning all elements.");
      LOG_INFO(" Please call PythonCreatorDescription.description.set_geometry_type")
      map->visitRo(*v);
      break;
  }
  // call this just in case there is some cleanup or unfinished matches
  v->finalizeMatches();

  const int matchesSizeAfter = matches.size();

  LOG_STATUS(
    "\tFound " << StringUtils::formatLargeNumber(v->getNumMatchCandidatesFound()) << " " <<
    matchType << " match candidates and " <<
    StringUtils::formatLargeNumber(matchesSizeAfter - matchesSizeBefore) <<
    " total matches in: " << StringUtils::millisecondsToDhms(timer.elapsed()) << ".");
}

vector<CreatorDescription> PythonMatchCreator::getAllCreators() const
{
  LOG_TRACE("getAllCreators");
  vector<CreatorDescription> result;

  for (shared_ptr<PythonCreatorDescription> desc : _creators)
  {
    result.push_back(*desc->getDescription());
  }

  return result;
}

PythonMatchVisitorPtr PythonMatchCreator::_getCachedVisitor(const ConstOsmMapPtr& map)
{
  LOG_TRACE("_getCachedVisitor");
  LOG_VART(_visitor.get());

  if (!_visitor || _visitor->getMap() != map)
  {
    LOG_TRACE("Resetting the match candidate checker: " <<
      _creatorInfo->getDescription()->getClassName() << "...");

    assert(_creatorInfo);
    assert(map);
    if (_filter == nullptr)
    {
      _filter = _creatorInfo->getCriterion();
    }
    PythonMatchVisitor* pmv = new PythonMatchVisitor(map, nullptr, getMatchThreshold(),
        _creatorInfo, _filter);
    _visitor.reset(pmv);
  }

  return _visitor;
}

ConstPythonCreatorDescriptionPtr PythonMatchCreator::getCreatorByName(const QString& name)
{
  for (PythonCreatorDescriptionPtr pcd : _creators)
  {
    if (pcd->getDescription()->getClassName() == name)
    {
      return pcd;
    }
  }
  return nullptr;
}

QStringList PythonMatchCreator::getCriteria() const
{
  // it would be nice to return the user register criterion but that doesn't work within this
  // interface.
  return QStringList{"PoiCriterion", "AreaCriterion"};
  //return _creatorInfo->getCriterion();
}

bool PythonMatchCreator::isMatchCandidate(ConstElementPtr element, const ConstOsmMapPtr& map)
{
  LOG_TRACE("isMatchCandidate");
  LOG_VAR(OsmJsonWriter().toString(map));
  // if (!_script)
  // {
  //   throw IllegalArgumentException("The script must be set on the PythonMatchCreator.");
  // }
  return _getCachedVisitor(map)->isMatchCandidate(element);
}

std::shared_ptr<MatchThreshold> PythonMatchCreator::getMatchThreshold()
{
  LOG_TRACE("getMatchThreshold");
  if (!_matchThreshold)
  {
    assert(_creatorInfo);

    _matchThreshold = _creatorInfo->getMatchThreshold();
  }
  return _matchThreshold;
}

QString PythonMatchCreator::getName() const
{
  // QFileInfo scriptFileInfo(_scriptPath);
  // return className() + ";" + scriptFileInfo.fileName();
  return "";
}

}
