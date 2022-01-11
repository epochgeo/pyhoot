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
#ifndef __PYTHON_MATCH_VISTOR_H__
#define __PYTHON_MATCH_VISTOR_H__

// hoot
#include <hoot/core/visitors/ConstElementVisitor.h>

// Qt
#include <QElapsedTimer>
#include <QHash>

// Standard
#include <deque>
#include <set>
#include <vector>

namespace hoot
{
  class ElementCriterion;
  class Match;
  class MatchThreshold;
  class OsmMap;

  using ElementCriterionPtr = std::shared_ptr<hoot::ElementCriterion>;
  using ConstMatchPtr = std::shared_ptr<const hoot::Match>;
  using ConstMatchThresholdPtr = std::shared_ptr<const hoot::MatchThreshold>;
  using OsmMapPtr = std::shared_ptr<hoot::OsmMap>;
  using ConstOsmMapPtr = std::shared_ptr<const hoot::OsmMap>;
}

namespace Tgs
{
  class HilbertRTree;
}

namespace hoot
{

using namespace hoot;

class PythonCreatorDescription;
using PythonCreatorDescriptionPtr = std::shared_ptr<PythonCreatorDescription>;

/**
 * Searches the specified map for any match potentials.
 */
class PythonMatchVisitor : public ConstElementVisitor
{
public:

  PythonMatchVisitor(const ConstOsmMapPtr& map, std::vector<ConstMatchPtr>* result,
    ConstMatchThresholdPtr mt, const PythonCreatorDescriptionPtr& pyInfo,
    ElementCriterionPtr filter = ElementCriterionPtr());

  ~PythonMatchVisitor() override = default;

  void initSearchRadiusInfo();

  QString getDescription() const override;
  QString getName() const override;
  QString getClassName() const override;

  void checkForMatch(const ConstElementPtr& e);

  ConstOsmMapPtr getMap() const;

  Meters getSearchRadius(const ConstElementPtr& e);

  void calculateSearchRadius();
  void cleanMapCache();

  std::shared_ptr<Tgs::HilbertRTree>& getIndex();

  /**
   * Returns true if e1, e2 is in the correct ordering for matching. This does a few things:
   *
   *  - Avoid comparing e1 to e2 and e2 to e1
   *  - The Unknown1/Input1 is always e1. This is a requirement for some of the older code.
   *  - Gives a consistent ordering to allow backwards compatibility with system tests.
   */
  bool isCorrectOrder(const ConstElementPtr& e1, const ConstElementPtr& e2) const;
  bool isMatchCandidate(ConstElementPtr e);

  void visit(const ConstElementPtr& e) override;

  double getCandidateDistanceSigma() const;
  void setCandidateDistanceSigma(double sigma);

  Meters getCustomSearchRadius() const;
  void setCustomSearchRadius(Meters searchRadius);

  std::vector<ConstMatchPtr>* getMatches() const { return _result; }

  long getNsInIsMatchPython() const { return _nsInIsMatch; }

  long getNumMatchCandidatesFound() const;

  /**
   * setResultVector sets the vector that results will be written to.
   * @brief setResultVector
   * @param result
   */
  void setResultVector(std::vector<ConstMatchPtr>* result) { _result = result; }

  // bool hasCustomSearchRadiusFunction() const { return !_getSearchRadius.IsEmpty(); }

private:

  // Don't hold on to the map.
  std::weak_ptr<const OsmMap> _map;

  QString _name;

  std::vector<ConstMatchPtr>* _result;
  ConstMatchThresholdPtr _mt;

  ElementCriterionPtr _filter;

  // used for automatic search radius calculation; it is expected that this is set from the
  // Javascript rules file used for the generic conflation
  double _customSearchRadius;

  int _neighborCountMax;
  int _neighborCountSum;
  int _elementsEvaluated;
  long _numElementsVisited;
  long _numMatchCandidatesVisited;
  long _nsInIsMatch;

  int _taskStatusUpdateInterval;
  int _memoryCheckUpdateInterval;

  long _totalElementsToProcess;

  //std::shared_ptr<ChainCriterion> _pointPolyCrit;

  QElapsedTimer _timer;

  PythonCreatorDescriptionPtr _pyInfo;

  QHash<ElementId, bool> _matchCandidateCache;
  QHash<ElementId, double> _searchRadiusCache;

  // Used for finding neighbors
  std::shared_ptr<Tgs::HilbertRTree> _index;
  std::deque<ElementId> _indexToEid;

  double _candidateDistanceSigma;

  QString _scriptPath;

  std::set<ElementId> _empty;
};

}

#endif
