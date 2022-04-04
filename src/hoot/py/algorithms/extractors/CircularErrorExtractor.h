/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#ifndef CIRCULARERROREXTRACTOR_H
#define CIRCULARERROREXTRACTOR_H

// hoot
#include <hoot/core/algorithms/extractors/FeatureExtractorBase.h>

namespace hoot
{

class OsmMap;
class Element;
using ConstElementPtr = std::shared_ptr<const Element>;

class CircularErrorExtractor : public FeatureExtractorBase
{
public:
  CircularErrorExtractor();
  /**
   * CircularErrorExtractor extracts the circular error from either the target or candidate element.
   * @param input 0 for target or 1 for candidate.
   */
  CircularErrorExtractor(int input);

  ~CircularErrorExtractor() = default;

  static QString className() { return "hoot::CircularErrorExtractor"; }

  double extract(const OsmMap& map, const ConstElementPtr& target,
    const ConstElementPtr& candidate) const override;
  virtual double extract(const ConstElementPtr& element) const;

  QString getDescription() const override { return "Extracts circular error"; }
  QString getClassName() const override { return className(); }
  QString getName() const override;

  QString toString() const { return getName(); }

private:
  int _input;
};

}

#endif // CIRCULARERROREXTRACTOR_H
