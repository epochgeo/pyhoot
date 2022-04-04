/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#ifndef TagMatchExtractor_H
#define TagMatchExtractor_H

// hoot
#include <hoot/core/algorithms/extractors/FeatureExtractorBase.h>

namespace hoot
{

class OsmMap;
class Element;
using ConstElementPtr = std::shared_ptr<const Element>;

/**
 * TagMatchExtractor extracts 1 if the specified key is the same for both features.
 */
class TagMatchExtractor : public FeatureExtractorBase
{
public:
  TagMatchExtractor();
  TagMatchExtractor(QString key);

  ~TagMatchExtractor() = default;

  static QString className() { return "hoot::TagMatchExtractor"; }

  double extract(const OsmMap& map, const ConstElementPtr& target,
    const ConstElementPtr& candidate) const override;

  QString getDescription() const override;
  QString getClassName() const override { return className(); }
  QString getName() const override;

  QString toString() const { return getName(); }

private:
  QString _key;
};

}

#endif // TagMatchExtractor_H
