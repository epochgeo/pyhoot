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

// pybind11
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace hoot
{
  class CreatorDescription;
  class Element;
  class ElementCriterion;
  class MatchClassification;
  class MatchThreshold;
  class OsmMap;

  using ConstElementPtr = std::shared_ptr<const Element>;
  using ConstOsmMapPtr = std::shared_ptr<const OsmMap>;
  using CreatorDescriptionPtr = std::shared_ptr<CreatorDescription>;
  using ElementCriterionPtr = std::shared_ptr<ElementCriterion>;
  using MatchClassificationPtr = std::shared_ptr<MatchClassification>;
  using MatchThresholdPtr = std::shared_ptr<MatchThreshold>;
}

namespace Tgs
{
  class DataFrame;
  using DataFramePtr = std::shared_ptr<DataFrame>;
  using ConstDataFramePtr = std::shared_ptr<const DataFrame>;
}

namespace hoot
{

using namespace Tgs;

using InitFunction = std::function<void(const ConstOsmMapPtr& map)>;
using ExtractFeaturesFunction = std::function< std::pair<Tgs::DataFramePtr, std::vector<bool> >(
  const ConstOsmMapPtr& map,
  const std::vector<ConstElementPtr>& elements1,
  const std::vector<ConstElementPtr>& elements2)>;
using IsMatchCandidateFunction = std::function<bool(
  const ConstOsmMapPtr& map,
  const std::vector<ConstElementPtr>& elements)>;
using IsWholeGroupFunction = std::function<bool()>;
using MatchScoreFunction = std::function<
  std::pair< pybind11::array_t<double, 3>, std::vector<QString> >(
    const ConstOsmMapPtr& map,
    const std::vector<ConstElementPtr>& elements1,
    const std::vector<ConstElementPtr>& elements2,
    const ConstDataFramePtr& dataFrame)>;
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
 * 
 * The visibility attribute gets rid of a warning during compile
 */
class __attribute__ ((visibility("hidden"))) PythonCreatorDescription
{
public:
  PythonCreatorDescription();
  ~PythonCreatorDescription();

  /**
   * clear clears all python references. This should be called before the app exists to avoid
   * leaks/hangs.
   */
  void clear();

  // remove me
  ElementCriterionPtr getCriterion() { return getMatchFromCriterion(); }

  CreatorDescriptionPtr getDescription();

  IsMatchCandidateFunction getIsMatchCandidate() const { return _isMatchCandidateFunc; }
  ExtractFeaturesFunction getExtractFeatures() const { return _extractFeaturesFunc; }
  /**
   * @brief getIsWholeGroup returns the function for determining if the matches should be treated
   * as groups.
   *
   * isWholeGroup() should be preferred as it will only call/cache the function once.
   */
  IsWholeGroupFunction getIsWholeGroup() const { return _isWholeGroupFunc; }
  ElementCriterionPtr getMatchFromCriterion() const { return _matchFromCriterion; }
  MatchScoreFunction getMatchScore() const { return _matchScoreFunc; }
  MatchThresholdPtr getMatchThreshold() const { return _matchThreshold; }
  ElementCriterionPtr getMatchToCriterion() const { return _matchToCriterion; }
  MergePairFunction getMergePair() const { return _mergePairFunc; }
  MergeSetFunction getMergeSet() const { return _mergeSetFunc; }
  Meters getSearchRadius() const { return _searchRadius; }
  SearchRadiusFunction getSearchRadiusFunction() const { return _searchRadiusFunc; }
  bool isWholeGroup() const { return _isWholeGroup; }


  // TODO remove me
  void setCriterion(ElementCriterionPtr crit) { setMatchFromCriterion(crit); }


  void setExtractFeatures(ExtractFeaturesFunction func) { _extractFeaturesFunc = func; }
  void setIsMatchCandidate(IsMatchCandidateFunction func);
  void setIsWholeGroup(IsWholeGroupFunction func);
  // TODO refactor so match criteria works for "from" and "to", this will enable us to have
  // a slightly lower complexity because at most from * to objects will need evaluating instead
  // of union(from, to) ^ 2
  void setMatchFromCriterion(ElementCriterionPtr criterion) { _matchFromCriterion = criterion; }
  void setMatchScore(MatchScoreFunction func) { _matchScoreFunc = func; }
  void setMatchThreshold(MatchThresholdPtr threshold) { _matchThreshold = threshold; }
  void setMatchToCriterion(ElementCriterionPtr criterion) { _matchToCriterion = criterion; }
  void setMergePair(MergePairFunction func) { _mergePairFunc = func; }
  void setMergeSet(MergeSetFunction func) { _mergeSetFunc = func; }
  void setSearchRadius(Meters radius);
  void setSearchRadiusFunction(SearchRadiusFunction func);

private:
  CreatorDescriptionPtr _desc;
  ExtractFeaturesFunction _extractFeaturesFunc;
  InitFunction _initFunc;
  IsMatchCandidateFunction _isMatchCandidateFunc;
  IsWholeGroupFunction _isWholeGroupFunc;
  mutable bool _isWholeGroup;

  ElementCriterionPtr _matchFromCriterion;
  MatchScoreFunction _matchScoreFunc;
  MatchThresholdPtr _matchThreshold;
  ElementCriterionPtr _matchToCriterion;
  MergePairFunction _mergePairFunc;
  MergeSetFunction _mergeSetFunc;

  Meters _searchRadius;
  SearchRadiusFunction _searchRadiusFunc;
};

}

#endif
