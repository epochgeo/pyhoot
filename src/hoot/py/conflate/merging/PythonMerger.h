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
#ifndef __PYTHON_MERGER_H__
#define __PYTHON_MERGER_H__

// hoot
#include <hoot/core/conflate/merging/MergerBase.h>

namespace hoot
{

class PythonCreatorDescription;
using ConstPythonCreatorDescriptionPtr = std::shared_ptr<const PythonCreatorDescription>;

/**
 * @sa PythonMatch
 */
class PythonMerger : public MergerBase
{
public:

  static QString className() { return "PythonMerger"; }

  static int logWarnCount;

  PythonMerger() = default;
  PythonMerger(const ConstPythonCreatorDescriptionPtr&,
    const std::set<std::pair<ElementId, ElementId>>& pairs);
  ~PythonMerger() override = default;

  void apply(const OsmMapPtr& map, std::vector<std::pair<ElementId, ElementId>>& replaced) override;

  QString toString() const override { return QString("PythonMerger"); }
  QString getDescription() const override
  { return "Merges elements matched with Generic Conflation"; }
  QString getName() const override { return className() + "-" + _matchType; }
  QString getClassName() const override { return className(); }

  void setMatchType(const QString& matchType) { _matchType = matchType; }

private:

  ConstPythonCreatorDescriptionPtr _pyInfo;
  ElementId _eid1, _eid2;
  QString _matchType;

  /**
   * _applyMergePair calls merge_pair in python.
   */
  virtual void _applyMergePair(
    const OsmMapPtr& map, std::vector<std::pair<ElementId, ElementId>>& replaced) const;

  /**
   * _applyMergeSet calls merge_set in python.
   */
  virtual void _applyMergeSets(
    const OsmMapPtr& map, std::vector<std::pair<ElementId, ElementId>>& replaced) const;
};

}

#endif
