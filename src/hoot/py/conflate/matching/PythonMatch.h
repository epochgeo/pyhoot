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
#ifndef __PYTHON_MATCH_H__
#define __PYTHON_MATCH_H__

// hoot
#include <hoot/core/conflate/matching/Match.h>
#include <hoot/core/conflate/matching/MatchThreshold.h>
#include <hoot/core/conflate/matching/MatchDetails.h>
#include <hoot/core/conflate/matching/MatchClassification.h>

namespace Tgs
{
  class DataFrame;
  using ConstDataFramePtr = std::shared_ptr<const DataFrame>;
  using DataFramePtr = std::shared_ptr<DataFrame>;
}

namespace hoot
{

class MatchClassification;
using MatchClassificationPtr = std::shared_ptr<MatchClassification>;

class PythonCreatorDescription;
using PythonCreatorDescriptionPtr = std::shared_ptr<PythonCreatorDescription>;

class PythonMatchTest;

/**
 * The python match routines are directly copied off the ScriptMatch JavaScript matching code in
 * Hootenanny. [1]
 * 
 * 1. https://github.com/ngageoint/hootenanny/blob/ea7613b4/hoot-js/src/main/cpp/hoot/js/conflate/matching/ScriptMatch.h
 */
class PythonMatch : public hoot::Match, public hoot::MatchDetails
{
public:

  static QString className() { return "PythonMatch"; }

  static int logWarnCount;

  PythonMatch() = default;
  PythonMatch(PythonCreatorDescriptionPtr pyInfo,
    const ConstOsmMapPtr& osmMap,
    const ElementId& eid1,
    const ElementId& eid2,
    const MatchClassificationPtr& matchClassification,
    const ConstMatchThresholdPtr& mt);
  ~PythonMatch() override = default;

  const MatchClassification& getClassification() const override { return *_p; }

  std::map<QString, double> getFeatures(const hoot::ConstOsmMapPtr& map) const override;

  hoot::MatchMembers getMatchMembers() const override { return _matchMembers; }
  void setMatchMembers(const hoot::MatchMembers& matchMembers) { _matchMembers = matchMembers; }

  QString explain() const override { return _explainText; }
  QString getName() const override { return _matchName; }

  double getProbability() const override;

  bool isConflicting(
    const hoot::ConstMatchPtr& other, const hoot::ConstOsmMapPtr& map,
    const QHash<QString, 
    hoot::ConstMatchPtr>& matches = QHash<QString, hoot::ConstMatchPtr>()) const override;

  bool isWholeGroup() const override;

  /**
   * Returns the two elements that were matched
   */
  std::set<std::pair<hoot::ElementId, hoot::ElementId>> getMatchPairs() const override;

  /**
   * setExtractedData sets a row of data that has been extracted to create this match.
   *
   * @param df is the DataFrame that contains the row of data.
   * @param row is the row index in df that contains this match's supporting data.
   */
  void setExtractedData(const Tgs::ConstDataFramePtr& df, unsigned int row);

  QString toString() const override;

  QString getClassName() const override { return className(); }
  QString getDescription() const override
  { return "Matches elements using Generic Conflation via Javascript"; }

  void setExplanation(const QString& ex) { _explainText = ex; }

private:

  friend class PythonMatchTest;

  /// _df is a dataframe that contains the extracted features for this match. This is optionally
  /// set with setExtractedData.
  Tgs::ConstDataFramePtr _df;
  /// _dfRow is the row that contains extracted data in _df.
  unsigned int _dfRow;

  bool _isWholeGroup;
  MatchMembers _matchMembers;
  QString _matchName;
  bool _neverCausesConflict;
  MatchClassificationPtr _p;
  PythonCreatorDescriptionPtr _pyInfo;

  QString _explainText;

  using ConflictKey = std::pair<hoot::ElementId, hoot::ElementId>;
  mutable QHash<ConflictKey, bool> _conflicts;

  void _calculateClassification(const hoot::ConstOsmMapPtr& map);

  ConflictKey _getConflictKey() const { return ConflictKey(_eid1, _eid2); }

  bool _isOrderedConflicting(const hoot::ConstOsmMapPtr& map, hoot::ElementId sharedEid,
    hoot::ElementId other1, hoot::ElementId other2,
    const QHash<QString, hoot::ConstMatchPtr>& matches = QHash<QString, hoot::ConstMatchPtr>())
      const;

  /*
   * Either creates a new match or retrieves an existing one from the global set of matches
   */
  // std::shared_ptr<const PythonMatch> _getMatch(
  //   hoot::OsmMapPtr map, v8::Local<v8::Object> mapJs, const ElementId& eid1, const ElementId& eid2,
  //   const QHash<QString, ConstMatchPtr>& matches) const;

};

}

#endif // __PYTHON_MATCH_H__
