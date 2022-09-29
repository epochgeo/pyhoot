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
 * Searches the specified map for match candidates.
 */
class PythonMatchVisitor : public ConstElementVisitor
{
public:

  PythonMatchVisitor(const ConstOsmMapPtr& map, std::vector<ConstMatchPtr>* result,
    ConstMatchThresholdPtr mt, const PythonCreatorDescriptionPtr& pyInfo,
    ElementCriterionPtr filter = ElementCriterionPtr());

  ~PythonMatchVisitor() override = default;

  /**
   * finalizeMatches finalizes any outstanding matches that may need to be evaluated due to
   * buffering. This _must_ be called after all elements have been processed with visit().
   */
  void finalizeMatches() { _flushBuffer(); }

  QString getDescription() const override;
  QString getName() const override;
  QString getClassName() const override;

  void checkForMatch(const ConstElementPtr& e);

  ConstOsmMapPtr getMap() const;

  /**
   * getMaxElementsInBuffer returns the maximum number of elements that should be stored up between
   * vectorized calls to python.
   */
  int getMaxElementsInBuffer() const { return 10000; }

  /**
   * getSearchRadius returns the search radius that should be used for e.
   *
   * This will call a user python script, if necessary. The result is cached so it can be called
   * repeatedly as needed.
   */
  Meters getSearchRadius(const ConstElementPtr& e);

  /**
   * getIndex builds the index (if needed) and returns the result. This will only contain element
   * that return true for isMatchCandidate().
   */
  std::shared_ptr<Tgs::HilbertRTree>& getIndex();

  /**
   * Returns true if e1, e2 is in the correct ordering for matching. This does a few things:
   *
   *  - Avoid comparing e1 to e2 and e2 to e1
   *  - The Unknown1/Input1 is always e1. This is a requirement for some of the older code.
   *  - Gives a consistent ordering to allow backwards compatibility with system tests.
   */
  bool isCorrectOrder(const ConstElementPtr& e1, const ConstElementPtr& e2) const;

  /**
   * isMatchCandidate returns true if e is a match candidate. If necessary, the user provided
   * python method will be called. The result is cached so it can be called repeatedly.
   */
  bool isMatchCandidate(ConstElementPtr e);

  void visit(const ConstElementPtr& e) override;

  Meters getCustomSearchRadius() const;
  void setCustomSearchRadius(Meters searchRadius);

  std::vector<ConstMatchPtr>* getMatches() const { return _result; }

  /**
   * getNumMatchCandidatesFound returns the number of match candidates that were visited.
   */
  long getNumMatchCandidatesFound() const;

  /**
   * setResultVector sets the vector that results will be written to.
   * @brief setResultVector
   * @param result
   */
  void setResultVector(std::vector<ConstMatchPtr>* result) { _result = result; }

  // bool hasCustomSearchRadiusFunction() const { return !_getSearchRadius.IsEmpty(); }

private:

  std::vector<ConstElementPtr> _buffer1;
  std::vector<ConstElementPtr> _buffer2;

  std::vector<ConstElementPtr> _isCandidate;

  // Don't hold on to the map.
  std::weak_ptr<const OsmMap> _map;

  QString _name;

  std::vector<ConstMatchPtr>* _result;
  ConstMatchThresholdPtr _mt;

  ElementCriterionPtr _filter;

  int _neighborCountMax;
  int _neighborCountSum;
  int _elementsEvaluated;
  long _numElementsVisited;
  long _numMatchCandidatesVisited;
  long _mapSize;

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

  void _flushBuffer();
};

}

#endif
