/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#ifndef StatusEqualsExtractor_H
#define StatusEqualsExtractor_H

// hoot
#include <hoot/core/algorithms/extractors/FeatureExtractorBase.h>

namespace hoot
{

class OsmMap;
class Element;
using ConstElementPtr = std::shared_ptr<const Element>;

/**
 * StatusEqualsExtractor extracts 1 if both elements match status or 0 otherwise.
 */
class StatusEqualsExtractor : public FeatureExtractorBase
{
public:
  StatusEqualsExtractor();
  StatusEqualsExtractor(Status status);

  ~StatusEqualsExtractor() = default;

  static QString className() { return "hoot::StatusEqualsExtractor"; }

  double extract(const OsmMap& map, const ConstElementPtr& target,
    const ConstElementPtr& candidate) const override;

  QString getDescription() const override { return "Extracts 1 if both features match the status"; }
  QString getClassName() const override { return className(); }
  QString getName() const override;

  QString toString() const { return getName(); }

private:
  Status _status;
};

}

#endif // StatusEqualsExtractor_H
