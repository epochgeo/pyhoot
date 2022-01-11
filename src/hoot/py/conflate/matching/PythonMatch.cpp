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

// Qt
#include <qnumeric.h>
#include <QElapsedTimer>
#include <QSet>

// Standard
#include <sstream>

using namespace hoot;
using namespace std;
using namespace Tgs;

namespace hoot
{

HOOT_FACTORY_REGISTER(hoot::Match, PythonMatch)

// void init_PythonMatch(py::module_& m)
// {
//     py::class_<PythonMatch>(m, "PythonMatch")
//         .def(py::init([](const ElementId& eid1, const ElementId& eid2, 
//             const ConstMatchThresholdPtr& mt) 
//           { 
//             return new PythonMatch(eid1, eid2, mt); }))
//         .def("explain", &PythonMatch::explain)
//         .def("getName", &PythonMatch::getName)
//     ;
// }

// REGISTER_PYHOOT_SUBMODULE(init_PythonMatch)

int PythonMatch::logWarnCount = 0;

PythonMatch::PythonMatch(PythonCreatorDescriptionPtr pyInfo,
  const ConstOsmMapPtr& osmMap,
  const ElementId& eid1,
  const ElementId& eid2,
  const ConstMatchThresholdPtr& mt) :
  Match(mt, eid1, eid2),
  _pyInfo(pyInfo),
  _isWholeGroup(false),
  _neverCausesConflict(false)
{
  _calculateClassification(osmMap);
}

void PythonMatch::_calculateClassification(const ConstOsmMapPtr& map)
{
  // Isolate* current = v8::Isolate::GetCurrent();
  // HandleScope handleScope(current);
  // Context::Scope context_scope(_script->getContext(current));
  // Local<Context> context = current->GetCurrentContext();

  // // removing these two lines causes a crash when checking for conflicts. WTF?
  // Local<Object> global = _script->getContext(current)->Global();
  // global->Get(context, toV8("plugin"));
  // if (plugin->Has(context, toV8("isWholeGroup")).ToChecked())
  // {
  //   Local<Value> v = _script->call(plugin, "isWholeGroup");
  //   _isWholeGroup = v->BooleanValue(current);
  // }

  // if (plugin->Has(context, toV8("neverCausesConflict")).ToChecked())
  // {
  //   Local<Value> v = _script->call(plugin, "neverCausesConflict");
  //   _neverCausesConflict = v->BooleanValue(current);
  // }

  // Local<String> featureTypeStr = String::NewFromUtf8(current, "baseFeatureType").ToLocalChecked();
  // if (plugin->Has(context, featureTypeStr).ToChecked())
  // {
  //   Local<Value> value = plugin->Get(context, featureTypeStr).ToLocalChecked();
  //   _matchName = toCpp<QString>(value);
  // }

  // try
  // {
  //   Local<Value> v = _call(map, mapObj, plugin);

  //   if (v.IsEmpty() || v->IsObject() == false)
  //   {
  //     throw IllegalArgumentException("Expected matchScore to return an associative array.");
  //   }

  //   QVariantMap vm = toCpp<QVariantMap>(v);
  //   // grab the match, miss, review results. If they aren't populated they get a value of 0.
  //   _p.setMatchP(_script->toNumber(v, "match", 0));
  //   _p.setMissP(_script->toNumber(v, "miss", 0));
  //   _p.setReviewP(_script->toNumber(v, "review", 0));

  //   _explainText = vm["explain"].toString();
  //   if (_explainText.isEmpty())
  //   {
  //     _explainText = _threshold->getTypeDetail(_p);
  //   }
  //   if (_threshold->getType(_p) == MatchType::Review && _explainText.isEmpty())
  //   {
  //     throw IllegalArgumentException(
  //       "If the match is a review an appropriate explanation must be provided (E.g. "
  //       "{ 'review': 1, 'explain': 'some reason' }.");
  //   }
  // }
  // catch (const NeedsReviewException& ex)
  // {
  //   LOG_VART(ex.getName());
  //   _p.setReview();
  //   _explainText = ex.getWhat();
  // }

  auto result = _pyInfo->getMatchScore()(map, map->getElement(_eid1), map->getElement(_eid2));
  _p = get<0>(result);
  _explainText = get<1>(result);
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

  // const PythonMatch* hm = dynamic_cast<const PythonMatch*>(other.get());
  // if (hm == nullptr)
  // {
  //   return true;
  // }
  // if (hm == this)
  // {
  //   return false;
  // }

  // // See ticket #5272
  // if (getClassification().getReviewP() == 1.0 || other->getClassification().getReviewP() == 1.0)
  // {
  //   return true;
  // }

  // ElementId sharedEid;
  // if (_eid1 == hm->_eid1 || _eid1 == hm->_eid2)
  // {
  //   sharedEid = _eid1;
  // }

  // if (_eid2 == hm->_eid1 || _eid2 == hm->_eid2)
  // {
  //   // both eids should never be the same.
  //   assert(sharedEid.isNull());
  //   sharedEid = _eid2;
  // }

  // // If the matches don't share at least one eid then it isn't a conflict.
  // if (sharedEid.isNull())
  // {
  //   return false;
  // }

  // // assign o1 and o2 to the non-shared eids
  // ElementId o1 = _eid1 == sharedEid ? _eid2 : _eid1;
  // ElementId o2 = hm->_eid1 == sharedEid ? hm->_eid2 : hm->_eid1;

  // bool foundCache = false;
  // bool cacheConflict = false;
  // QHash<ConflictKey, bool>::const_iterator cit1 = _conflicts.find(hm->_getConflictKey());
  // if (cit1 != _conflicts.end())
  // {
  //   foundCache = true;
  //   cacheConflict = cit1.value();
  // }
  // QHash<ConflictKey, bool>::const_iterator cit2 = hm->_conflicts.find(_getConflictKey());
  // if (cit2 != hm->_conflicts.end())
  // {
  //   foundCache = true;
  //   cacheConflict = cit2.value();
  // }

  // if (foundCache)
  // {
  //   conflicting = cacheConflict;
  // }
  // else
  // {
  //   try
  //   {
  //     // We need to check for a conflict in two directions. If its conflicting when we merge the
  //     // shared EID with this class first, then is it a conflict if we merge with the other EID
  //     // first.
  //     if (_isOrderedConflicting(map, sharedEid, o1, o2, matches) ||
  //         hm->_isOrderedConflicting(map, sharedEid, o2, o1, matches))
  //     {
  //       conflicting = true;
  //     }
  //     else
  //     {
  //       conflicting = false;
  //     }
  //   }
  //   catch (const NeedsReviewException& /*e*/)
  //   {
  //     conflicting = true;
  //   }
  //   _conflicts[hm->_getConflictKey()] = conflicting;
  // }

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

// std::shared_ptr<const PythonMatch> PythonMatch::_getMatch(
//   OsmMapPtr map, const ElementId& eid1, const ElementId& eid2,
//   const QHash<QString, ConstMatchPtr>& matches) const
// {
//   std::shared_ptr<const PythonMatch> match;

//   QString matchKey;
//   if (eid1 < eid2)
//   {
//     matchKey = eid1.toString() + "," + eid2.toString();
//   }
//   else
//   {
//     matchKey = eid2.toString() + "," + eid1.toString();
//   }
//   QHash<QString, ConstMatchPtr>::const_iterator itr = matches.find(matchKey);
//   if (itr != matches.end())
//   {
//     std::shared_ptr<const PythonMatch> scriptMatch =
//       std::dynamic_pointer_cast<const PythonMatch>(itr.value());
//     if (scriptMatch)
//     {
//       match = scriptMatch;
//       LOG_TRACE("Match cache hit for: " << matchKey);
//     }
//   }

//   if (!match)
//   {
//     match = std::make_shared<PythonMatch>(_script, _plugin, map, mapJs, eid1, eid2, _threshold);
//   }

//   return match;
// }

bool PythonMatch::isWholeGroup() const
{
  auto func = _pyInfo->getIsWholeGroup();
  if (func != nullptr) return func();
  return false;
}

// Local<Value> PythonMatch::_call(
//   const ConstOsmMapPtr& map, Local<Object> mapObj, Local<Object> plugin)
// {
//   Isolate* current = v8::Isolate::GetCurrent();
//   EscapableHandleScope handleScope(current);
//   Context::Scope context_scope(_script->getContext(current));
//   Local<Context> context = current->GetCurrentContext();

//   Local<Value> value = plugin->Get(context, toV8("matchScore")).ToLocalChecked();
//   Local<Function> func = Local<Function>::Cast(value);
//   Local<Value> jsArgs[3];

//   if (func.IsEmpty() || func->IsFunction() == false)
//     throw IllegalArgumentException("matchScore must be a valid function.");

//   int argc = 0;
//   jsArgs[argc++] = mapObj;
//   jsArgs[argc++] = ElementJs::New(map->getElement(_eid1));
//   jsArgs[argc++] = ElementJs::New(map->getElement(_eid2));

//   LOG_VART(map->getElement(_eid1).get());
//   LOG_VART(map->getElement(_eid2).get());
//   LOG_TRACE("Calling script matcher...");

//   TryCatch trycatch(current);
//   MaybeLocal<Value> maybe_result = func->Call(context, plugin, argc, jsArgs);
//   if (maybe_result.IsEmpty())
//     HootExceptionJs::throwAsHootException(trycatch);

//   Local<Value> result = maybe_result.ToLocalChecked();
//   HootExceptionJs::checkV8Exception(result, trycatch);

//   return handleScope.Escape(result);
// }

// Local<Value> PythonMatch::_callGetMatchFeatureDetails(const ConstOsmMapPtr& map) const
// {
//   Isolate* current = v8::Isolate::GetCurrent();
//   EscapableHandleScope handleScope(current);
//   Context::Scope context_scope(_script->getContext(current));
//   Local<Context> context = current->GetCurrentContext();

//   Local<Object> plugin =
//     Local<Object>::Cast(
//       _script->getContext(current)->Global()->Get(context, toV8("plugin")).ToLocalChecked());
//   Local<Value> value = plugin->Get(context, toV8("getMatchFeatureDetails")).ToLocalChecked();
//   Local<Function> func = Local<Function>::Cast(value);
//   Local<Value> jsArgs[3];

//   if (func.IsEmpty() || func->IsFunction() == false)
//     throw IllegalArgumentException(
//       "getMatchFeatureDetails must be a valid function for match from: " + _matchName);

//   Local<Object> mapObj = OsmMapJs::create(map);

//   int argc = 0;
//   jsArgs[argc++] = mapObj;
//   jsArgs[argc++] = ElementJs::New(map->getElement(_eid1));
//   jsArgs[argc++] = ElementJs::New(map->getElement(_eid2));

//   TryCatch trycatch(current);
//   MaybeLocal<Value> maybe_result = func->Call(context, plugin, argc, jsArgs);
//   if (maybe_result.IsEmpty())
//       HootExceptionJs::throwAsHootException(trycatch);

//   Local<Value> result = maybe_result.ToLocalChecked();
//   HootExceptionJs::checkV8Exception(result, trycatch);

//   return handleScope.Escape(result);
// }

std::map<QString, double> PythonMatch::getFeatures(const ConstOsmMapPtr& map) const
{
  std::map<QString, double> result;
  // LOG_TRACE("Calling getMatchFeatureDetails...");
  // Local<Value> v = _callGetMatchFeatureDetails(map);

  // if (v.IsEmpty() || v->IsObject() == false)
  // {
  //   throw IllegalArgumentException(
  //     "Expected getMatchFeatureDetails to return an associative array.");
  // }

  // QVariantMap vm = toCpp<QVariantMap>(v);
  // long valCtr = 0;
  // LOG_VART(vm.size());
  // for (QVariantMap::const_iterator it = vm.begin(); it != vm.end(); ++it)
  // {
  //   if (it.value().isNull() == false)
  //   {
  //     double d = it.value().toDouble();
  //     result[it.key()] = d;
  //     if (::qIsNaN(result[it.key()]))
  //     {
  //       if (logWarnCount < Log::getWarnMessageLimit())
  //       {
  //         LOG_WARN("found NaN feature value for: " << it.key());
  //       }
  //       else if (logWarnCount == Log::getWarnMessageLimit())
  //       {
  //         LOG_WARN(className() << ": " << Log::LOG_WARN_LIMIT_REACHED_MESSAGE);
  //       }
  //       logWarnCount++;
  //     }
  //   }
  //   valCtr++;
  // }

  // if (vm.size() > 0)
  // {
  //   LOG_DEBUG("Processed " << vm.size() << " sample values.");
  // }

  return result;
}

QString PythonMatch::toString() const
{
  stringstream ss;
  ss << _matchName.toStdString() << "Match: " << _eid1 << ", " << _eid2 << " p: " << 
    _p->toString().toStdString();
  return QString::fromStdString(ss.str());
}

}
