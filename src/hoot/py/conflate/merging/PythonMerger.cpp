/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. Maxar
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 */
#include "PythonMerger.h"

// hoot
#include <hoot/core/index/OsmMapIndex.h>
#include <hoot/core/util/Factory.h>

#include <hoot/py/conflate/matching/PythonCreatorDescription.h>

using namespace std;

namespace hoot
{

HOOT_FACTORY_REGISTER(Merger, PythonMerger)

int PythonMerger::logWarnCount = 0;

PythonMerger::PythonMerger(
  const ConstPythonCreatorDescriptionPtr& pyInfo,
  const set<pair<ElementId, ElementId>>& pairs) :
  MergerBase(pairs),
  _pyInfo(pyInfo)
{
  _eid1 = _pairs.begin()->first;
  _eid2 = _pairs.begin()->second;
}

void PythonMerger::apply(const OsmMapPtr& map, vector<pair<ElementId, ElementId>>& replaced)
{
  bool hasMergeSet = _pyInfo->getMergeSet() != nullptr;
  bool hasMergePair = _pyInfo->getMergePair() != nullptr;

  if (hasMergeSet == hasMergePair)
  {
    throw HootException("The merging script must implement exactly one of mergeSet or mergePair.");
  }
  else if (hasMergeSet)
  {
    _applyMergeSets(map, replaced);
  }
  else
  {
    _applyMergePair(map, replaced);
  }
}

void PythonMerger::_applyMergePair(
  const OsmMapPtr& map, vector<pair<ElementId, ElementId>>& replaced) const
{
  LOG_VART(_eid1);
  LOG_VART(_eid2);
  LOG_VART(_pairs.size());

  const bool mapContainsElement1 = map->containsElement(_eid1);
  const bool mapContainsElement2 = map->containsElement(_eid2);
  // This contains and following pair size checks were put in place as the result of changing
  // MergerFactory to not throw an exception when a merger cannot be found for a set of match pairs.
  if (!mapContainsElement1 || !mapContainsElement2)
  {
    if (logWarnCount < Log::getWarnMessageLimit())
    {
      LOG_WARN("Attempting to merge one or more elements that do not exist: ");
      if (!mapContainsElement1)
      {
        LOG_WARN(_eid1);
      }
      if (!mapContainsElement2)
      {
        LOG_WARN(_eid2);
      }
    }
    else if (logWarnCount == Log::getWarnMessageLimit())
    {
      LOG_WARN(className() << ": " << Log::LOG_WARN_LIMIT_REACHED_MESSAGE);
    }
    logWarnCount++;
    return;
  }
  else if (_pairs.empty())
  {
    if (logWarnCount < Log::getWarnMessageLimit())
    {
      LOG_WARN("Attempting to merge empty element pairs.");
    }
    else if (logWarnCount == Log::getWarnMessageLimit())
    {
      LOG_WARN(className() << ": " << Log::LOG_WARN_LIMIT_REACHED_MESSAGE);
    }
    logWarnCount++;
    return;
  }
  else if (_pairs.size() > 1)
  {
    throw HootException(
      "A set of elements was specified, but only mergePairs is implemented. See the _Supplemental "
      "User Documentation_, _Conflating Sets_ for details.");
  }

  ConstElementPtr newElement = _pyInfo->getMergePair()(map, map->getElement(_eid1),
    map->getElement(_eid2));

  if (!newElement || map->containsElement(newElement) == false)
  {
    throw InternalErrorException("The merging script must return the merged element.");
  }

  LOG_VART(map->containsElement(_eid1));
  if (map->containsElement(_eid1) == false)
  {
    replaced.emplace_back(_eid1, newElement->getElementId());
  }
  LOG_VART(map->containsElement(_eid2));
  if (map->containsElement(_eid2) == false)
  {
    replaced.emplace_back(_eid2, newElement->getElementId());
  }
}

void PythonMerger::_applyMergeSets(
  const OsmMapPtr& map, vector<pair<ElementId, ElementId>>& replaced) const
{
  assert(_pyInfo->getMergeSet() != nullptr);
  assert(map != nullptr);

  auto newReplaced = _pyInfo->getMergeSet()(map, _pairs);
  replaced.insert(replaced.end(), newReplaced.begin(), newReplaced.end());

  // TODO: Verify that all the elements are where they need to be (e.g. were removed from the map or
  // added to the map as needed).
}

}
