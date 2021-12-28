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
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/util/Configurable.h>

namespace hoot
{

class PythonCreatorDescription;
using PythonCreatorDescriptionPtr = std::shared_ptr<PythonCreatorDescription>;
using ConstPythonCreatorDescriptionPtr = std::shared_ptr<const PythonCreatorDescription>;

class PythonMatchVisitor;
using PythonMatchVisitorPtr = std::shared_ptr<PythonMatchVisitor>;

/**
 * Match creator for all generic conflation scripts
 *
 * @sa ScriptMatch
 */
class PythonMatchCreator : public MatchCreator, public SearchRadiusProvider, public Configurable
{
public:

  static QString className() { return "PythonMatchCreator"; }

  PythonMatchCreator();
  ~PythonMatchCreator() override = default;

  /**
   * @see SearchRadiusProvider
   */
  void init(const ConstOsmMapPtr& map) override;
  
  /**
   * @see SearchRadiusProvider
   */
  Meters calculateSearchRadius(const ConstOsmMapPtr& map, const ConstElementPtr& e) override;

  static void clear();

  /**
   * @see Configurable
   */
  void setConfiguration(const Settings& conf) override;

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
   * getCreatorByName returns the creator python info for a specified name.
   */
  static ConstPythonCreatorDescriptionPtr getCreatorByName(const QString& name);

  /**
   * registerCreator registers a description so it can be accessed via the MatchFactory.
   */
  static void registerCreator(PythonCreatorDescriptionPtr desc) { _creators.append(desc); }

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

  QString _name;

  friend class PythonMatchCreatorTest;

  PythonMatchVisitorPtr _visitor;

  /// _creatorInfo contains all the Python script pointers and relevant names.
  PythonCreatorDescriptionPtr _creatorInfo;

  QStringList _criteria;

  std::shared_ptr<MatchThreshold> _matchThreshold;

  static QList<PythonCreatorDescriptionPtr> _creators;

  ElementCriterionPtr _pointPolyPolyCrit;
  ElementCriterionPtr _pointPolyPointCrit;

  PythonMatchVisitorPtr _getCachedVisitor(const ConstOsmMapPtr& map);

  hoot::CreatorDescription _getScriptDescription(QString path) const;
};

}

#endif // __PYTHON_MATCH_CREATOR_H__
