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
#include "PythonMatch.h"

// hoot
#include <hoot/core/conflate/matching/MatchClassification.h>
#include <hoot/core/conflate/matching/MatchType.h>
#include <hoot/core/conflate/merging/Merger.h>
#include <hoot/core/ops/CopyMapSubsetOp.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/util/Log.h>
#include <hoot/py/conflate/matching/PythonCreatorDescription.h>

// pybind11
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

// Qt
#include <qnumeric.h>
#include <QElapsedTimer>
#include <QSet>

// Standard
#include <sstream>

// tgs
#include <tgs/RandomForest/DataFrame.h>

namespace py = pybind11;
using namespace std;
using namespace Tgs;

namespace hoot
{

HOOT_FACTORY_REGISTER(hoot::Match, PythonMatch)

int PythonMatch::logWarnCount = 0;

PythonMatch::PythonMatch(PythonCreatorDescriptionPtr pyInfo,
  const ConstOsmMapPtr& osmMap,
  const ElementId& eid1,
  const ElementId& eid2,
  const MatchClassificationPtr& matchClassification,
  const ConstMatchThresholdPtr& mt) :
  Match(mt, eid1, eid2),
  _pyInfo(pyInfo),
  _p(matchClassification),
  _isWholeGroup(false),
  _neverCausesConflict(false)
{
}

set<pair<ElementId, ElementId>> PythonMatch::getMatchPairs() const
{
  set<pair<ElementId, ElementId>> result;
  result.emplace(_eid1, _eid2);
  return result;
}

double PythonMatch::getProbability() const
{
  return _p->getMatchP();
}

bool PythonMatch::isConflicting(
  const ConstMatchPtr& other, const ConstOsmMapPtr& map,
  const QHash<QString, ConstMatchPtr>& matches) const
{
  LOG_TRACE("Checking for match conflict...");

  if (_neverCausesConflict)
  {
    return false;
  }

  bool conflicting = false;


  return conflicting;

}

bool PythonMatch::_isOrderedConflicting(
  const ConstOsmMapPtr& map, ElementId sharedEid, ElementId other1, ElementId other2,
  const QHash<QString, ConstMatchPtr>& matches) const
{
  LOG_TRACE("Checking " << other1 << " and " << other2 << " for order conflict...");

//   Isolate* current = v8::Isolate::GetCurrent();
//   HandleScope handleScope(current);
//   Context::Scope context_scope(_script->getContext(current));

//   set<ElementId> eids;
//   eids.emplace(sharedEid);
//   eids.emplace(other1);
//   eids.emplace(other2);

//   OsmMapPtr copiedMap = std::make_shared<OsmMap>(map->getProjection());
//   CopyMapSubsetOp(map, eids).apply(copiedMap);
//   Local<Object> copiedMapJs = OsmMapJs::create(copiedMap);

//   // make sure unknown1 is always first
//   ElementId eid11, eid12, eid21, eid22;
//   if (map->getElement(sharedEid)->getStatus() == Status::Unknown1)
//   {
//     eid11 = sharedEid;
//     eid21 = sharedEid;
//     eid12 = other1;
//     eid22 = other2;
//   }
//   else
//   {
//     eid11 = other1;
//     eid21 = other2;
//     eid12 = sharedEid;
//     eid22 = sharedEid;
//   }

//   LOG_VART(eid11);
//   LOG_VART(eid12);
//   // This and the other commented block of code below are an attempt to prevent script matching
//   // being executed on non-candidate matches, during match conflict resolution. These changes cause
//   // regression test failures, and it isn't clear why at this point.
// //  if (!_isMatchCandidate(copiedMap->getElement(eid11), copiedMap) ||
// //      !_isMatchCandidate(copiedMap->getElement(eid12), copiedMap))
// //  {
// //    LOG_TRACE("Skipping non-match candidate from pair 1: " << eid11 << ", " << eid12 << "...");
// //    return true;
// //  }

//   std::shared_ptr<const PythonMatch> m1 = _getMatch(copiedMap, copiedMapJs, eid11, eid12, matches);
//   MatchSet ms;
//   ms.emplace(m1);
//   vector<MergerPtr> mergers;
//   ScriptMergerCreator creator;
//   creator.createMergers(ms, mergers);

//   // If we got a merger, then check to see if it conflicts.
//   if (mergers.size() == 1)
//   {
//     // apply the merger to our map copy
//     vector<pair<ElementId, ElementId>> replaced;
//     mergers[0]->apply(copiedMap, replaced);

//     // replace the element id in the second merger
//     for (size_t i = 0; i < replaced.size(); ++i)
//     {
//       if (replaced[i].first == eid21)
//       {
//         eid21 = replaced[i].second;
//       }
//       if (replaced[i].first == eid22)
//       {
//         eid22 = replaced[i].second;
//       }
//     }

//     // If we can still find the second match after the merge was applied, then it isn't a conflict.
//     if (copiedMap->containsElement(eid21) && copiedMap->containsElement(eid22))
//     { 
//       LOG_VART(eid21);
//       LOG_VART(eid22);
// //      if (!_isMatchCandidate(copiedMap->getElement(eid21), copiedMap) ||
// //          !_isMatchCandidate(copiedMap->getElement(eid22), copiedMap))
// //      {
// //        LOG_TRACE("Skipping non-match candidate from pair 2: " << eid21 << ", " << eid22 << "...");
// //        //return true;
// //        return false;
// //      }

//       std::shared_ptr<const PythonMatch> m2 =
//         _getMatch(copiedMap, copiedMapJs, eid21, eid22, matches);
//       if (m2->getType() == MatchType::Match)
//       {
//         return false;
//       }
//     }
//   }

  return true;
}

bool PythonMatch::isWholeGroup() const
{
  return _pyInfo->isWholeGroup();
}

std::map<QString, double> PythonMatch::getFeatures(const ConstOsmMapPtr& map) const
{
  std::map<QString, double> result;
  for (unsigned int i = 0; i < _df->getNumFactors(); i++)
  {
    QString fname = QString::fromStdString(_df->getFactorLabels()[i]);
    result[fname] = _df->getDataVector(_dfRow)[i];
  }

  return result;
}

void PythonMatch::setExtractedData(const Tgs::ConstDataFramePtr& df, unsigned int row)
{
  _df = df;
  _dfRow = row;
}

QString PythonMatch::toString() const
{
  stringstream ss;
  ss << _matchName.toStdString() << "Match: " << _eid1 << ", " << _eid2 << " p: " << 
    _p->toString().toStdString();
  return QString::fromStdString(ss.str());
}

}
