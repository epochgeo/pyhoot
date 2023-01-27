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
#include <hoot/core/criterion/AreaCriterion.h>
#include <hoot/core/criterion/ChainCriterion.h>
#include <hoot/core/criterion/LinearCriterion.h>
#include <hoot/core/criterion/NonConflatableCriterion.h>
#include <hoot/core/criterion/PointCriterion.h>
#include <hoot/core/elements/MapProjector.h>
#include <hoot/core/index/OsmMapIndex.h>
#include <hoot/core/info/CreatorDescription.h>
#include <hoot/core/util/Log.h>
#include <hoot/core/util/MemoryUsageChecker.h>
#include <hoot/core/util/StringUtils.h>
#include <hoot/core/visitors/SpatialIndexer.h>

// pyhoot
#include <hoot/py/conflate/matching/PythonCreatorDescription.h>
#include <hoot/py/conflate/matching/PythonMatch.h>

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

namespace hoot
{

PythonMatchVisitor::PythonMatchVisitor(const ConstOsmMapPtr& map,
  vector<ConstMatchPtr>* result,
  ConstMatchThresholdPtr mt,
  const PythonCreatorDescriptionPtr& pyInfo,
  ElementCriterionPtr filter) :
  _map(map),
  _mt(mt),
  _pyInfo(pyInfo),
  _filter(filter),
  _neighborCountMax(-1),
  _neighborCountSum(0),
  _elementsEvaluated(0),
  _numElementsVisited(0),
  _numMatchCandidatesVisited(0),
  _mapSize(map->size()),
  _taskStatusUpdateInterval(ConfigOptions().getTaskStatusUpdateInterval()),
  _memoryCheckUpdateInterval(ConfigOptions().getMemoryUsageCheckerInterval()),
  _totalElementsToProcess(0)
{
  LOG_TRACE("PythonMatchVisitor");

  // TODO remove me, see PythonCreatorDescription::setMatchFromCriterion
  LOG_TRACE("Unknown2 is being ignored during match making. Please fix.")
  if (!MapProjector::isPlanar(map))
  {
    throw HootException("map must be in a planar projection.");
  }

  assert(_mt);

  // Calls to script functions/var are expensive, both memory-wise and processing-wise. Since this
  // constructor gets called repeatedly by createMatch, keep those calls out of this constructor.

  // Point/Polygon is not meant to conflate any polygons that are conflatable by other *specific*
  // alg conflation routines (generic geometry algs should be ignored here), hence the use of
  // NonConflatableCriterion.
  shared_ptr<NonConflatableCriterion> nonConflatableCrit =
    make_shared<NonConflatableCriterion>(map);
  nonConflatableCrit->setIgnoreGenericConflators(true);
  // _pointPolyCrit =
  //   make_shared<ChainCriterion>(make_shared<PolygonCriterion>(map), nonConflatableCrit);

  _timer.start();
}

void PythonMatchVisitor::_flushBuffer()
{
  LOG_TRACE("_flushBuffer()...");
  ConstOsmMapPtr map = getMap();

  pair<DataFramePtr, vector<bool> > res = _pyInfo->getExtractFeatures()(map, _buffer1, _buffer2);
  DataFramePtr df = res.first;
  vector<bool> ignored = res.second;

  LOG_VART(_buffer1.size());
  LOG_VART(_buffer2.size());
  if (!_buffer1.empty() && !_buffer2.empty())
  {
    pair< py::array_t<double, 3>, vector<QString> > result = _pyInfo->getMatchScore()(map,
      _buffer1, _buffer2, df);
    py::array_t<double, 3>& scores = result.first;
    vector<QString>& reasons = result.second;
    assert(_buffer1.size() == reasons.size());
    assert(_buffer1.size() == scores.size() / 3);
    PointCriterion pointC(map);
    LinearCriterion linearC;
    AreaCriterion areaC(map);

    for (size_t i = 0; i < _buffer1.size(); i++)
    {
      //_p = get<0>(result);
      //_explainText = get<1>(result);
      // skip all the hard ignores
      if (ignored[i]) continue;

      MatchClassificationPtr matchClassification = make_shared<MatchClassification>(scores.at(i, 0),
        scores.at(i, 1), scores.at(i, 2));

      ConstElementPtr e1 = _buffer1[i];
      ConstElementPtr e2 = _buffer2[i];

      // Score each candidate and push it on the result vector.
      shared_ptr<PythonMatch> m = make_shared<PythonMatch>(_pyInfo, map, e1->getElementId(),
        e2->getElementId(), matchClassification, _mt);
      m->setExplanation(reasons[i]);
      m->setExtractedData(df, i);
      MatchMembers mm;

      // if we're confident this is not a miss
      if (m->getType() != MatchType::Miss)
      {
        MatchMembers mm;
        // derive the match members. This differs from the JavaScript interface.
        if (pointC.isSatisfied(e1)) mm = mm | MatchMembers::Poi;
        if (linearC.isSatisfied(e1)) mm = mm | MatchMembers::Polyline;
        if (areaC.isSatisfied(e1)) mm = mm | MatchMembers::Polygon;
        if (pointC.isSatisfied(e2)) mm = mm | MatchMembers::Poi;
        if (linearC.isSatisfied(e2)) mm = mm | MatchMembers::Polyline;
        if (areaC.isSatisfied(e2)) mm = mm | MatchMembers::Polygon;

        m->setMatchMembers(mm);
        _result->push_back(m);
      }
    }
  }
  
  _buffer1.clear();
  _buffer2.clear();
  LOG_TRACE("..._flushBuffer()");
}

QString PythonMatchVisitor::getDescription() const { return ""; }
QString PythonMatchVisitor::getName() const { return _name; }
QString PythonMatchVisitor::getClassName() const { return ""; }

void PythonMatchVisitor::checkForMatch(const ConstElementPtr& e)
{
  LOG_TRACE("checkForMatch");

  LOG_VART(e->getElementId());

  // TODO remove me, see PythonCreatorDescription::setMatchFromCriterion
  if (e->getStatus() == Status::Unknown1)
  {
    return;
  }

  ConstOsmMapPtr map = getMap();

  // create an envelope around the e plus the search radius.
  shared_ptr<Envelope> env(e->getEnvelope(map));
  Meters searchRadius = getSearchRadius(e);
  LOG_VART(searchRadius);
  env->expandBy(searchRadius);
  LOG_VART(env);

  // find other nearby candidates
  LOG_TRACE(
    "Finding neighbors for: " << e->getElementId() << " during conflation: " << _scriptPath <<
    "...");
  const set<ElementId> neighbors =
    SpatialIndexer::findNeighbors(*env, getIndex(), _indexToEid, map);
  ElementId from = e->getElementId();

  _elementsEvaluated++;

  QElapsedTimer timer;

  for (ElementId eid : neighbors)
  {
    // don't match from to from
    if (eid == from) continue;

    ConstElementPtr e2 = map->getElement(eid);
    LOG_VART(e->getTags().getName());
    LOG_VART(e->getStatus());
    LOG_VART(e->getElementId());
    LOG_VART(e2->getStatus());
    LOG_VART(e2->getTags().getName());
    LOG_VART(e2->getElementId());

    // isCorrectOrder and isMatchCandidate don't apply to Point/Polygon, so we add a different
    // workflow for it here. All other generic scripts use isMatchCandidate to identify both
    // what to index and what to match and that doesn't work for Point/Polygon matching two
    // different geometries. See related note in getIndex about Point/Polygon.

    bool attemptToMatch = false;
    LOG_VART(isCorrectOrder(e, e2));
    LOG_VART(isMatchCandidate(e2));
    // TODO fix me, see PythonCreatorDescription::setMatchFromCriterion
    // attemptToMatch = (e2->getStatus() == Status::Unknown1 || isCorrectOrder(e, e2)) &&
    //   isMatchCandidate(e2);
    // Skipping the isCorrectOrder stipulation since Unknown1 will always be considered to be the
    // reference dataset for now.
    attemptToMatch = e2->getStatus() == Status::Unknown1 && isMatchCandidate(e2);
    LOG_VART(attemptToMatch);

    if (attemptToMatch)
    {
      timer.restart();

      _buffer1.push_back(e);
      _buffer2.push_back(e2);
      if (_buffer1.size() >= getMaxElementsInBuffer())
      {
        _flushBuffer();
      }
    }
  }

  _neighborCountSum += neighbors.size();
  _neighborCountMax = max(_neighborCountMax, (int)neighbors.size());
}

ConstOsmMapPtr PythonMatchVisitor::getMap() const { return _map.lock(); }

Meters PythonMatchVisitor::getSearchRadius(const ConstElementPtr& e)
{
  LOG_TRACE("getSearchRadius");
  // See the "Calculating Search Radius" section in the user docs for more information.

  Meters result;
  auto func = _pyInfo->getSearchRadiusFunction();

  if (func != nullptr)
  {
    if (_searchRadiusCache.contains(e->getElementId()))
    {
      result = _searchRadiusCache[e->getElementId()];
    }
    else
    {
      result = func(e);
      _searchRadiusCache[e->getElementId()] = result;
    }
  }
  else
  {
    result = _pyInfo->getSearchRadius();
  }

  return result;
}

shared_ptr<HilbertRTree>& PythonMatchVisitor::getIndex()
{
  LOG_TRACE("getIndex");
  if (!_index)
  {
    LOG_INFO("Creating script feature index for: " << _pyInfo->getDescription()->getClassName() <<
      "...");

    // Not tuned
    _index = make_shared<Tgs::HilbertRTree>(make_shared<Tgs::MemoryPageStore>(728), 2);

    // Only index elements that satisfy the isMatchCandidate. Previously we only indexed Unknown2,
    // but that causes issues when wanting to conflate from n datasets and support intra-dataset
    // conflation. This approach over-indexes a bit and will likely slow things down, but should
    // give the same results. An option in the future would be to support an "isIndexedFeature" or
    // similar function to speed the operation back up again.

    long numElementsIndexed = 0;

    // create an isMatchCandidate criterion
    function<bool (ConstElementPtr)> f =
      bind(&PythonMatchVisitor::isMatchCandidate, this, placeholders::_1);
    shared_ptr<ArbitraryCriterion> pC = make_shared<ArbitraryCriterion>(f);

    ConstOsmMapPtr osmMap = _map.lock();
    SpatialIndexer v(_index,
      _indexToEid,
      pC,
      bind(&PythonMatchVisitor::getSearchRadius, this, placeholders::_1),
      getMap());
    switch (_pyInfo->getDescription()->getBaseFeatureType())
    {
      case CreatorDescription::BaseFeatureType::POI:
      case CreatorDescription::BaseFeatureType::Point:
        LOG_DEBUG("visit nodes");
        osmMap->visitNodesRo(v);
        _totalElementsToProcess = osmMap->getNodeCount();
        break;
      case CreatorDescription::BaseFeatureType::Highway:
      case CreatorDescription::BaseFeatureType::Building:
      case CreatorDescription::BaseFeatureType::River:
      case CreatorDescription::BaseFeatureType::PoiPolygonPOI:
      case CreatorDescription::BaseFeatureType::Polygon:
      case CreatorDescription::BaseFeatureType::Area:
      case CreatorDescription::BaseFeatureType::Railway:
      case CreatorDescription::BaseFeatureType::PowerLine:
      case CreatorDescription::BaseFeatureType::Line:
        osmMap->visitWaysRo(v);
        osmMap->visitRelationsRo(v);
        _totalElementsToProcess = osmMap->getWayCount();
        break;
      case CreatorDescription::BaseFeatureType::Relation:
        osmMap->visitRelationsRo(v);
        _totalElementsToProcess = osmMap->getRelationCount();
        break;
      case CreatorDescription::BaseFeatureType::Unknown:
        osmMap->visitRo(v);
        _totalElementsToProcess = osmMap->size();
        break;
      default:
        // TODO: Downgrading log message until issues can be fixed in the unit tests.
        // visit all geometry types if the script didn't identify its geometry
        LOG_DEBUG("Unrecognized geometry type, scanning all elements.");
        LOG_DEBUG(" Please call PythonCreatorDescription.description.set_geometry_type")
        osmMap->visitRo(v);
        _totalElementsToProcess = osmMap->size();
        break;
    }
    v.finalizeIndex();
    numElementsIndexed = v.getSize();

    LOG_INFO(
     "Script feature index created for: " << _pyInfo->getDescription()->getClassName() <<
     " with " << StringUtils::formatLargeNumber(numElementsIndexed) << " elements.");
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
  LOG_TRACE("isCorrectOrder");
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
  LOG_TRACE("isMatchCandidate");
  bool result = false;

  if (_matchCandidateCache.contains(e->getElementId()))
  {
    result = _matchCandidateCache[e->getElementId()];
  }
  else if (_filter && !_filter->isSatisfied(e))
  {
    result = false;
  }
  else
  {
    auto func = _pyInfo->getIsMatchCandidate();
    if (!func)
    {
      result = true;
    }
    else
    {
      // TODO replace isMatchCandidate with a bulk operation
      result = func(_map.lock(), vector<ConstElementPtr>{e});
      _matchCandidateCache[e->getElementId()] = result;
    }
  }
  LOG_VART(e->getTags().getName());
  LOG_VART(e->getElementId());
  LOG_VART(result);

  return result;
}

void PythonMatchVisitor::visit(const ConstElementPtr& e)
{
  LOG_TRACE("visit");
  if (isMatchCandidate(e))
  {
    checkForMatch(e);

    _numMatchCandidatesVisited++;
    //if (_numMatchCandidatesVisited % (_taskStatusUpdateInterval * 100) == 0)
    if (_numMatchCandidatesVisited % 100 == 0)
    {
      PROGRESS_STATUS(
        "\tProcessed " << StringUtils::formatLargeNumber(_numMatchCandidatesVisited) <<
        " match candidates / " << StringUtils::formatLargeNumber(_totalElementsToProcess) <<
        " total elements.");
    }
  }

  _numElementsVisited++;
  if (_numElementsVisited % 1000 == 0)
  {
    PROGRESS_STATUS(
      "\tProcessed " << StringUtils::formatLargeNumber(_numElementsVisited) << " of " <<
      StringUtils::formatLargeNumber(_mapSize) << " elements.");
  }
}

long PythonMatchVisitor::getNumMatchCandidatesFound() const { return _numMatchCandidatesVisited; }

}
