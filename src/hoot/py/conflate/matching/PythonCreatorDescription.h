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
#ifndef __PYTHON_CREATOR_DESCRIPTION_H__
#define __PYTHON_CREATOR_DESCRIPTION_H__

// hoot
#include <hoot/core/elements/ElementId.h>
#include <hoot/core/util/Units.h>

namespace hoot
{
  class CreatorDescription;
  class Element;
  class MatchClassification;
  class MatchThreshold;
  class OsmMap;

  using ConstElementPtr = std::shared_ptr<const Element>;
  using ConstOsmMapPtr = std::shared_ptr<const OsmMap>;
  using CreatorDescriptionPtr = std::shared_ptr<CreatorDescription>;
  using MatchClassificationPtr = std::shared_ptr<MatchClassification>;
  using MatchThresholdPtr = std::shared_ptr<MatchThreshold>;
}

namespace hoot
{

using namespace hoot;

using InitFunction = std::function<void(const ConstOsmMapPtr& map)>;
using IsMatchCandidateFunction = std::function<bool(
  const ConstOsmMapPtr& map,
  const ConstElementPtr& element)>;
using IsWholeGroupFunction = std::function<bool()>;
using MatchScoreFunction = std::function<
std::tuple<MatchClassificationPtr, QString>(
  const ConstOsmMapPtr& map,
  const ConstElementPtr& element1,
  const ConstElementPtr& element2)>;
using MergePairFunction = std::function<ConstElementPtr(
  const ConstOsmMapPtr& map,
  const ConstElementPtr& element1,
  const ConstElementPtr& element2)>;
using MergeSetFunction = std::function<
  std::vector<std::pair<ElementId, ElementId>>(
    const ConstOsmMapPtr& map,
    const std::set<std::pair<ElementId, ElementId>>& pairs)>;
using SearchRadiusFunction = std::function<Meters(const ConstElementPtr& e)>;

/**
 * PythonCreatorDescription describes a python script creator. E.g. the callback functions, name
 * etc.
 */
class PythonCreatorDescription
{
public:
  PythonCreatorDescription();
  ~PythonCreatorDescription();

  /**
   * clear clears all python references.
   */
  void clear();

  QStringList getCriteria() const { return _criteria; }
  CreatorDescriptionPtr getDescription();
  IsMatchCandidateFunction getIsMatchCandidate() const { return _isMatchCandidateFunc; }
  IsWholeGroupFunction getIsWholeGroup() const { return _isWholeGroupFunc; }
  MatchScoreFunction getMatchScore() const { return _matchScoreFunc; }
  MatchThresholdPtr getMatchThreshold() const { return _matchThreshold; }
  MergePairFunction getMergePair() const { return _mergePairFunc; }
  MergeSetFunction getMergeSet() const { return _mergeSetFunc; }
  Meters getSearchRadius() const { return _searchRadius; }
  SearchRadiusFunction getSearchRadiusFunction() const { return _searchRadiusFunc; }

  void setCriteria(QStringList criteria) { _criteria = criteria; }
  void setIsMatchCandidate(IsMatchCandidateFunction func);
  void setIsWholeGroup(IsWholeGroupFunction func) { _isWholeGroupFunc = func; }
  void setMatchScore(MatchScoreFunction func) { _matchScoreFunc = func; }
  void setMatchThreshold(MatchThresholdPtr threshold) { _matchThreshold = threshold; }
  void setMergePair(MergePairFunction func) { _mergePairFunc = func; }
  void setMergeSet(MergeSetFunction func) { _mergeSetFunc = func; }
  void setSearchRadius(Meters radius);
  void setSearchRadiusFunction(SearchRadiusFunction func);

private:
  QStringList _criteria;
  CreatorDescriptionPtr _desc;
  InitFunction _initFunc;
  IsMatchCandidateFunction _isMatchCandidateFunc;
  IsWholeGroupFunction _isWholeGroupFunc;

  MatchScoreFunction _matchScoreFunc;
  MatchThresholdPtr _matchThreshold;
  MergePairFunction _mergePairFunc;
  MergeSetFunction _mergeSetFunc;

  Meters _searchRadius;
  SearchRadiusFunction _searchRadiusFunc;
};

}

#endif
