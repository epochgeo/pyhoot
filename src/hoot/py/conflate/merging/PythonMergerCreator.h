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
#ifndef __PYTHON_MERGER_CREATOR_H__
#define __PYTHON_MERGER_CREATOR_H__

// hoot
#include <hoot/core/conflate/merging/MergerCreator.h>

namespace hoot
{

class PythonCreatorDescription;
using PythonCreatorDescriptionPtr = std::shared_ptr<PythonCreatorDescription>;

/**
 * @sa PythonMatchCreator
 */
class PythonMergerCreator : public MergerCreator
{
public:

  static QString className() { return "PythonMergerCreator"; }

  PythonMergerCreator();
  ~PythonMergerCreator() override = default;

  static void clear();

  /**
   * If all the matches are CustomPoiMatches, a single CustomPoiMerger will be created and returned.
   */
  bool createMergers(const MatchSet& matches, std::vector<MergerPtr>& mergers) const override;

  std::vector<CreatorDescription> getAllCreators() const override;

  bool isConflicting(const ConstOsmMapPtr& map, ConstMatchPtr m1, ConstMatchPtr m2,
    const QHash<QString, ConstMatchPtr>& matches = QHash<QString, ConstMatchPtr>()) const override;

  /**
   * registerCreator registers a description so it can be accessed via the MatchFactory.
   */
  static void registerCreator(const PythonCreatorDescriptionPtr& desc) { _creators.append(desc); }

  void setArguments(QStringList args) override;

private:
  PythonCreatorDescriptionPtr _pyInfo;

  static QList<PythonCreatorDescriptionPtr> _creators;
};

}

#endif
