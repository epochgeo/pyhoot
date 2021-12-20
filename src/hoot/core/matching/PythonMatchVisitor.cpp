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
#include "PythonMatchVisitor.h"

// hoot
#include <hoot/core/conflate/matching/MatchThreshold.h>
#include <hoot/core/conflate/matching/MatchType.h>
#include <hoot/core/criterion/ArbitraryCriterion.h>
#include <hoot/core/criterion/StatusCriterion.h>
#include <hoot/core/index/OsmMapIndex.h>
#include <hoot/core/info/CreatorDescription.h>
#include <hoot/core/schema/OsmSchema.h>
#include <hoot/core/util/ConfPath.h>
#include <hoot/core/util/ConfigOptions.h>
#include <hoot/core/util/Factory.h>
#include <hoot/core/util/StringUtils.h>
#include <hoot/core/visitors/ElementConstOsmMapVisitor.h>
#include <hoot/core/visitors/SpatialIndexer.h>
#include <hoot/core/criterion/PolygonCriterion.h>
#include <hoot/core/criterion/NonConflatableCriterion.h>
#include <hoot/core/criterion/PointCriterion.h>
#include <hoot/core/criterion/ChainCriterion.h>
#include <hoot/core/util/MemoryUsageChecker.h>
#include <hoot/core/geometry/ElementToGeometryConverter.h>

// Qt
#include <QElapsedTimer>

// Standard
#include <functional>
#include <cmath>

// TGS
#include <tgs/RStarTree/IntersectionIterator.h>
#include <tgs/RStarTree/MemoryPageStore.h>

using namespace geos::geom;
using namespace std;
using namespace Tgs;

namespace py = pybind11;

using namespace Tgs;

namespace hoot
{

PythonMatchVisitor::PythonMatchVisitor(const ConstOsmMapPtr& map, vector<ConstMatchPtr>& result,
  ConstMatchThresholdPtr mt, ElementCriterionPtr filter) :
  _map(map),
  _result(result),
  _mt(mt),
  // _script(script),
  _filter(filter),
  _customSearchRadius(-1.0),
  _neighborCountMax(-1),
  _neighborCountSum(0),
  _elementsEvaluated(0),
  _numElementsVisited(0),
  _numMatchCandidatesVisited(0),
  _taskStatusUpdateInterval(ConfigOptions().getTaskStatusUpdateInterval()),
  _memoryCheckUpdateInterval(ConfigOptions().getMemoryUsageCheckerInterval()),
  _totalElementsToProcess(0)
{
  // Calls to script functions/var are expensive, both memory-wise and processing-wise. Since this
  // constructor gets called repeatedly by createMatch, keep those calls out of this constructor.

  // Point/Polygon is not meant to conflate any polygons that are conflatable by other *specific*
  // alg conflation routines (generic geometry algs should be ignored here), hence the use of
  // NonConflatableCriterion.
  std::shared_ptr<NonConflatableCriterion> nonConflatableCrit =
    std::make_shared<NonConflatableCriterion>(map);
  nonConflatableCrit->setIgnoreGenericConflators(true);
  _pointPolyCrit =
    std::make_shared<ChainCriterion>(std::make_shared<PolygonCriterion>(map), nonConflatableCrit);

  _timer.start();
}

void PythonMatchVisitor::initSearchRadiusInfo()
{
  LOG_DEBUG("Initializing search radius info...");

  // _candidateDistanceSigma = getNumber(plugin, "candidateDistanceSigma", 0.0, 1.0);

  // //this is meant to have been set externally in a js rules file
  // _customSearchRadius =
  //   getNumber(plugin, "searchRadius", -1.0, ConfigOptions().getCircularErrorDefaultValue());
  // LOG_VARD(_customSearchRadius);

  // Local<Value> value = plugin->Get(context, toV8("getSearchRadius")).ToLocalChecked();
  // if (value->IsUndefined())
  // {
  //   // pass
  // }
  // else if (value->IsFunction() == false)
  // {
  //   throw HootException("getSearchRadius is not a function.");
  // }
  // else
  // {
  //   _getSearchRadius.Reset(current, Local<Function>::Cast(value));
  // }
}

QString PythonMatchVisitor::getDescription() const { return ""; }
QString PythonMatchVisitor::getName() const { return _name; }
QString PythonMatchVisitor::getClassName() const { return ""; }

void PythonMatchVisitor::checkForMatch(const std::shared_ptr<const Element>& e)
{
  // Isolate* current = v8::Isolate::GetCurrent();
  // HandleScope handleScope(current);
  // Context::Scope context_scope(_script->getContext(current));
  // Persistent<Object> plugin(current, getPlugin(_script));
  // Local<Object> mapJs(ToLocal(&_mapJs));

  // LOG_VART(e->getElementId());

  // ConstOsmMapPtr map = getMap();

  // // create an envelope around the e plus the search radius.
  // std::shared_ptr<Envelope> env(e->getEnvelope(map));
  // Meters searchRadius = getSearchRadius(e);
  // LOG_VART(searchRadius);
  // env->expandBy(searchRadius);
  // LOG_VART(env);

  // // find other nearby candidates
  // LOG_TRACE(
  //   "Finding neighbors for: " << e->getElementId() << " during conflation: " << _scriptPath <<
  //   "...");
  // const set<ElementId> neighbors =
  //   SpatialIndexer::findNeighbors(*env, getIndex(), _indexToEid, map);
  // LOG_VART(neighbors);
  // ElementId from = e->getElementId();

  // _elementsEvaluated++;

  // const bool isPointPolyConflation =
  //   _scriptPath.contains(PythonMatchCreator::POINT_POLYGON_SCRIPT_NAME);
  // for (set<ElementId>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
  // {
  //   ConstElementPtr e2 = map->getElement(*it);
  //   LOG_VART(e2->getElementId());

  //   // isCorrectOrder and isMatchCandidate don't apply to Point/Polygon, so we add a different
  //   // workflow for it here. All other generic scripts use isMatchCandidate to identify both
  //   // what to index and what to match and that doesn't work for Point/Polygon matching two
  //   // different geometries. See related note in getIndex about Point/Polygon.

  //   bool attemptToMatch = false;
  //   if (!isPointPolyConflation)
  //   {
  //     LOG_VART(isCorrectOrder(e, e2));
  //     LOG_VART(isMatchCandidate(e2));
  //     attemptToMatch = isCorrectOrder(e, e2) && isMatchCandidate(e2);
  //   }
  //   else
  //   {
  //     attemptToMatch = _pointPolyCrit->isSatisfied(e2);
  //   }
  //   LOG_VART(attemptToMatch);

  //   if (attemptToMatch)
  //   {
  //     // Score each candidate and push it on the result vector.
  //     std::shared_ptr<ScriptMatch> m =
  //       std::make_shared<ScriptMatch>(_script, plugin, map, mapJs, from, *it, _mt);
  //     m->setMatchMembers(
  //       ScriptMatch::geometryTypeToMatchMembers(
  //         GeometryTypeCriterion::typeToString(_scriptInfo.getGeometryType())));
  //     // if we're confident this is not a miss
  //     if (m->getType() != MatchType::Miss)
  //     {
  //       _result.push_back(m);
  //     }
  //   }
  // }

  // _neighborCountSum += neighbors.size();
  // _neighborCountMax = std::max(_neighborCountMax, (int)neighbors.size());
}

ConstOsmMapPtr PythonMatchVisitor::getMap() const { return _map.lock(); }

Meters PythonMatchVisitor::getSearchRadius(const ConstElementPtr& e)
{
  // See the "Calculating Search Radius" section in the user docs for more information.

  Meters result = 0;
  // if (_getSearchRadius.IsEmpty())
  // {
  //   if (_customSearchRadius < 0)
  //   {
  //     // base the radius off of the element itself
  //     LOG_TRACE("Calculating search radius based off of element...");
  //     result = e->getCircularError() * _candidateDistanceSigma;
  //   }
  //   else
  //   {
  //     // base the radius off some predefined radius
  //     LOG_TRACE("Calculating search radius based off of custom defined script value...");
  //     result = _customSearchRadius * _candidateDistanceSigma;
  //   }
  // }
  // else
  // {
  //   if (_searchRadiusCache.contains(e->getElementId()))
  //   {
  //     LOG_TRACE("Retrieving search radius from cache...");
  //     result = _searchRadiusCache[e->getElementId()];
  //   }
  //   else
  //   {
  //     LOG_TRACE("Calling getSearchRadius function for: " << _scriptPath << "...");

  //     Isolate* current = v8::Isolate::GetCurrent();
  //     HandleScope handleScope(current);
  //     Context::Scope context_scope(_script->getContext(current));
  //     Local<Context> context = current->GetCurrentContext();

  //     Local<Value> jsArgs[1];

  //     int argc = 0;
  //     jsArgs[argc++] = ElementJs::New(e);

  //     Local<Value> f =
  //       ToLocal(&_getSearchRadius)->Call(context, getPlugin(), argc, jsArgs).ToLocalChecked();

  //     result = toCpp<Meters>(f) * _candidateDistanceSigma;

  //     _searchRadiusCache[e->getElementId()] = result;
  //   }
  // }

  // LOG_VART(result);
  return result;
}

void PythonMatchVisitor::calculateSearchRadius()
{
  // // This is meant to run one time when the match creator is initialized. We're either getting
  // // the search radius from a predefined property linked to a config option in the conflate rules
  // // file or we're calculating it with a function call from the rules file. Either way, then we're
  // // caching it after the first retrieval.

  // LOG_DEBUG("Checking for existence of search radius export for: " << _scriptPath << "...");

  // Isolate* current = v8::Isolate::GetCurrent();
  // HandleScope handleScope(current);
  // Context::Scope context_scope(_script->getContext(current));
  // Local<Context> context = current->GetCurrentContext();

  // Persistent<Object> plugin(current, getPlugin(_script));
  // Local<String> initStr = String::NewFromUtf8(current, "calculateSearchRadius").ToLocalChecked();
  // // optional method, so don't throw an error
  // if (ToLocal(&plugin)->Has(context, initStr).ToChecked() == false)
  // {
  //   LOG_TRACE("calculateSearchRadius function not present.");
  //   return;
  // }
  // Local<Value> value = ToLocal(&plugin)->Get(context, initStr).ToLocalChecked();
  // if (value->IsFunction() == false)
  // {
  //   LOG_TRACE("calculateSearchRadius function not present.");
  //   return;
  // }

  // LOG_DEBUG("Getting search radius for: " << _scriptPath << "...");

  // Local<Function> func = Local<Function>::Cast(value);
  // Local<Value> jsArgs[1];
  // int argc = 0;
  // assert(getMap().get());
  // OsmMapPtr copiedMap = std::make_shared<OsmMap>(getMap());
  // jsArgs[argc++] = OsmMapJs::create(copiedMap);

  // Local<Value> c = func->Call(context, ToLocal(&plugin), argc, jsArgs).ToLocalChecked();
  // LOG_DEBUG("Return value: " << c);

  // // This could be an expensive call.
  // _customSearchRadius =
  //   getNumber(
  //     ToLocal(&plugin), "searchRadius", -1.0, ConfigOptions().getCircularErrorDefaultValue());

  // QFileInfo scriptFileInfo(_scriptPath);
  // LOG_DEBUG(
  //   "Search radius of: " << _customSearchRadius << " to be used for: " <<
  //   scriptFileInfo.fileName());
}

void PythonMatchVisitor::cleanMapCache()
{
}

std::shared_ptr<HilbertRTree>& PythonMatchVisitor::getIndex()
{
  if (!_index)
  {
    LOG_INFO("Creating script feature index for: " << _scriptPath << "...");

    // No tuning was done, just copied these settings from OsmMapIndex. 10 children - 368 - see
    // #3054
    _index = std::make_shared<Tgs::HilbertRTree>(std::make_shared<Tgs::MemoryPageStore>(728), 2);

    // Only index elements that satisfy the isMatchCandidate. Previously we only indexed Unknown2,
    // but that causes issues when wanting to conflate from n datasets and support intra-dataset
    // conflation. This approach over-indexes a bit and will likely slow things down, but should
    // give the same results. An option in the future would be to support an "isIndexedFeature" or
    // similar function to speed the operation back up again.

    // Point/Polygon conflation behaves diferently than all other generic scripts in that it
    // conflates geometries of different types. This class wasn't really originally designed to
    // handle that, so we add a logic path here to accommodate it.
    long numElementsIndexed = 0;
    //if (!_scriptPath.contains(PythonMatchCreator::POINT_POLYGON_SCRIPT_NAME))
    assert(false);
    if (true)
    {
      std::function<bool (ConstElementPtr)> f =
        std::bind(&PythonMatchVisitor::isMatchCandidate, this, placeholders::_1);
      std::shared_ptr<ArbitraryCriterion> pC = std::make_shared<ArbitraryCriterion>(f);

      SpatialIndexer v(_index,
                       _indexToEid,
                       pC,
                       std::bind(&PythonMatchVisitor::getSearchRadius, this, placeholders::_1),
                       getMap());
      switch (_scriptInfo.getGeometryType())
      {
        case GeometryTypeCriterion::GeometryType::Point:
          getMap()->visitNodesRo(v);
          break;
        case GeometryTypeCriterion::GeometryType::Line:
          getMap()->visitWaysRo(v);
          getMap()->visitRelationsRo(v);
          break;
        case GeometryTypeCriterion::GeometryType::Polygon:
          getMap()->visitWaysRo(v);
          getMap()->visitRelationsRo(v);
          break;
        default:
          // visit all geometry types if the script didn't identify its geometry
          getMap()->visitRo(v);
          break;
      }
      v.finalizeIndex();
      numElementsIndexed = v.getSize();
    }
    else
    {
      // Point/Polygon identifies points as match candidates, so we just index all polygons here.
      SpatialIndexer v(_index,
                       _indexToEid,
                       _pointPolyCrit,
                       std::bind(&PythonMatchVisitor::getSearchRadius, this, placeholders::_1),
                       getMap());
      getMap()->visitWaysRo(v);
      getMap()->visitRelationsRo(v);
      v.finalizeIndex();
      numElementsIndexed = v.getSize();
    }

    LOG_INFO(
      "Script feature index created for: " << _scriptPath << " with " <<
      StringUtils::formatLargeNumber(numElementsIndexed) << " elements.");
  }
  return _index;
}

/**
 * Returns true if e1, e2 is in the correct ordering for matching. This does a few things:
 *
 *  - Avoid comparing e1 to e2 and e2 to e1
 *  - The Unknown1/Input1 is always e1. This is a requirement for some of the older code.
 *  - Gives a consistent ordering to allow backwards compatibility with system tests.
 */
bool PythonMatchVisitor::isCorrectOrder(const ConstElementPtr& e1, const ConstElementPtr& e2) const
{
  LOG_VART(e1->getStatus().getEnum());
  LOG_VART(e2->getStatus().getEnum());
  LOG_VART(e1->getElementId());
  LOG_VART(e2->getElementId());

  if (e1->getStatus().getEnum() == e2->getStatus().getEnum())
  {
    return e1->getElementId() < e2->getElementId();
  }
  else
  {
    return e1->getStatus().getEnum() < e2->getStatus().getEnum();
  }
}

bool PythonMatchVisitor::isMatchCandidate(ConstElementPtr e)
{
  if (_matchCandidateCache.contains(e->getElementId()))
  {
    return _matchCandidateCache[e->getElementId()];
  }

  if (_filter && !_filter->isSatisfied(e))
  {
    return false;
  }

  bool result = false;

  // // TODO: Prioritize exports.matchCandidateCriterion over the isMatchCandidate function and use
  // // the crit instead of the function; doing so causes this to crash; see #3047 and the history
  // // of this file for the failing code that needs to be re-enabled

  // Local<String> isMatchCandidateStr =
  //   String::NewFromUtf8(current, "isMatchCandidate").ToLocalChecked();
  // if (ToLocal(&plugin)->Has(context, isMatchCandidateStr).ToChecked() == false)
  // {
  //   throw HootException("Error finding 'isMatchCandidate' function.");
  // }
  // Local<Value> value = ToLocal(&plugin)->Get(context, isMatchCandidateStr).ToLocalChecked();
  // if (value->IsFunction() == false)
  // {
  //   throw HootException("isMatchCandidate is not a function.");
  // }
  // Local<Function> func = Local<Function>::Cast(value);
  // Local<Value> jsArgs[2];

  // int argc = 0;
  // jsArgs[argc++] = getOsmMapJs();
  // jsArgs[argc++] = ElementJs::New(e);

  // Local<Value> f = func->Call(context, ToLocal(&plugin), argc, jsArgs).ToLocalChecked();

  // result = f->BooleanValue(current);

  // _matchCandidateCache[e->getElementId()] = result;

  return result;
}

void PythonMatchVisitor::visit(const ConstElementPtr& e)
{
  if (isMatchCandidate(e))
  {
    checkForMatch(e);

    _numMatchCandidatesVisited++;
    if (_numMatchCandidatesVisited % (_taskStatusUpdateInterval * 100) == 0)
    {
      PROGRESS_DEBUG(
        "\tProcessed " << StringUtils::formatLargeNumber(_numMatchCandidatesVisited) <<
        " match candidates / " << StringUtils::formatLargeNumber(_totalElementsToProcess) <<
        " total elements.");
    }
  }

  // if matching gets slow, throttle the log update interval accordingly.
  if (_timer.elapsed() > 3000 && _taskStatusUpdateInterval >= 10)
  {
    _taskStatusUpdateInterval /= 10;
  }
  else if (_timer.elapsed() < 250 && _taskStatusUpdateInterval < 10000)
  {
    _taskStatusUpdateInterval *= 10;
  }

  _numElementsVisited++;
  if (_numElementsVisited % _taskStatusUpdateInterval == 0)
  {
    PROGRESS_STATUS(
      "\tProcessed " << StringUtils::formatLargeNumber(_numElementsVisited) << " of " <<
      StringUtils::formatLargeNumber(_totalElementsToProcess) << " elements.");
     _timer.restart();
  }
  if (_numElementsVisited % _memoryCheckUpdateInterval == 0)
  {
    MemoryUsageChecker::getInstance().check();
  }
}

void PythonMatchVisitor::setScriptPath(QString path) { _scriptPath = path; }
QString PythonMatchVisitor::getScriptPath() const { return _scriptPath; }

Meters PythonMatchVisitor::getCustomSearchRadius() const { return _customSearchRadius; }
void PythonMatchVisitor::setCustomSearchRadius(Meters searchRadius) 
{
  _customSearchRadius = searchRadius;
}

double PythonMatchVisitor::getCandidateDistanceSigma() const { return _candidateDistanceSigma; }
void PythonMatchVisitor::setCandidateDistanceSigma(double sigma)
{
  _candidateDistanceSigma = sigma;
}

CreatorDescription PythonMatchVisitor::getCreatorDescription() const { return _scriptInfo; }
void PythonMatchVisitor::setCreatorDescription(const CreatorDescription& description)
{
  _scriptInfo = description;

  if (_scriptPath.toLower().contains("relation")) // hack
  {
    _totalElementsToProcess = getMap()->getRelationCount();
  }
  else
  {
    switch (_scriptInfo.getGeometryType())
    {
      case GeometryTypeCriterion::GeometryType::Point:
        _totalElementsToProcess = getMap()->getNodeCount();
        break;
      case GeometryTypeCriterion::GeometryType::Line:
        _totalElementsToProcess = getMap()->getWayCount() + getMap()->getRelationCount();
        break;
      case GeometryTypeCriterion::GeometryType::Polygon:
        _totalElementsToProcess = getMap()->getWayCount() + getMap()->getRelationCount();
        break;
      default:
        // visit all geometry types if the script didn't identify its geometry
        _totalElementsToProcess = getMap()->size();
        break;
    }
  }
}

long PythonMatchVisitor::getNumMatchCandidatesFound() const { return _numMatchCandidatesVisited; }

// bool hasCustomSearchRadiusFunction() const { return !_getSearchRadius.IsEmpty(); }

}
