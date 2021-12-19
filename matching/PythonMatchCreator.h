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
#ifndef __PYTHON_MATCH_CREATOR_H__
#define __PYTHON_MATCH_CREATOR_H__

// Hoot
#include <hoot/core/conflate/SearchRadiusProvider.h>
#include <hoot/core/conflate/matching/MatchCreator.h>
#include <hoot/core/criterion/ElementCriterion.h>
#include <hoot/core/util/Configurable.h>

namespace hoot
{

/**
 * Match creator for all generic conflation scripts
 *
 * @sa ScriptMatch
 */
class PythonMatchCreator : public MatchCreator, public SearchRadiusProvider, public Configurable
{
public:

  static QString className() { return "PythonMatchCreator"; }

  static const QString POINT_POLYGON_SCRIPT_NAME;

  PythonMatchCreator();
  ~PythonMatchCreator() override = default;kkkkkkkkj

  /**
   * @see SearchRadiusProvider
   */
  void init(const ConstOsmMapPtr& map) override;
  
  /**
   * @see SearchRadiusProvider
   */
  Meters calculateSearchRadius(const ConstOsmMapPtr& map, const ConstElementPtr& e) override;

  /**
   * @see Configurable
   */
  void setConfiguration(const Settings& conf) override;

  /**
   * setInitFunction is optionally called by python to set this class's initialization function.
   */
  void setInitFunction(std::function<void(const ConstOsmMapPtr& map)> func);

  /**
   * @see MatchCreator
   */
  MatchPtr createMatch(const ConstOsmMapPtr&, ElementId, ElementId) override;
  /**
   * Search the provided map for POI matches and add the matches to the matches vector.
   */
  void createMatches(
    const ConstOsmMapPtr& map, std::vector<ConstMatchPtr>& matches,
    ConstMatchThresholdPtr threshold) override;
  /**
   * Determines whether an element is a candidate for matching for this match creator
   *
   * @param element element to determine the match candidate status of
   * @param map the map the element whose candidacy is being determined belongs to
   * @return true if the element is a match candidate; false otherwise
   */
  bool isMatchCandidate(ConstElementPtr element, const ConstOsmMapPtr& map) override;
  /**
   * @see MatchCreator
   */
  std::shared_ptr<MatchThreshold> getMatchThreshold() override;

  /**
   * @see MatchCreator
   */
  std::vector<CreatorDescription> getAllCreators() const override;

  /**
   * @see MatchCreator
   */
  void setArguments(const QStringList& args) override;

  /**
   * @see MatchCreator
   */
  QString getName() const override;

  /**
   * @see FilteredByGeometryTypeCriteria
   */
  QStringList getCriteria() const override;

  void setName(const QString& name) { _name = name; }

private:

  /// _initFunction is called before any matching is done.
  std::function<void(const ConstOsmMapPtr& map)> _initFunction;
  QString _name;

  friend class PythonMatchCreatorTest;

  QString _scriptPath;
  CreatorDescription _scriptInfo;

  std::shared_ptr<MatchThreshold> _matchThreshold;
  QMap<QString, Meters> _cachedCustomSearchRadii;
  QMap<QString, double> _candidateDistanceSigmaCache;
  QMap<QString, CreatorDescription> _descriptionCache;

  ElementCriterionPtr _pointPolyPolyCrit;
  ElementCriterionPtr _pointPolyPointCrit;

  hoot::CreatorDescription _getScriptDescription(QString path) const;
  /**
   * @brief _validateConfigOptions validates configuration options for the specified feature type
   * being conflated
   * @param baseFeatureType the type of feature to conflate
   */
  void _validateConfig(const hoot::CreatorDescription::BaseFeatureType& baseFeatureType);
};

}

#endif // __PYTHON_MATCH_CREATOR_H__
