/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "TagMatchExtractor.h"

// hoot
#include <hoot/core/util/Factory.h>
#include <hoot/core/algorithms/string/LevenshteinDistance.h>

using namespace std;

namespace hoot
{

HOOT_FACTORY_REGISTER(FeatureExtractor, TagMatchExtractor)

TagMatchExtractor::TagMatchExtractor(QString key) :
  _key(key)
{
}

TagMatchExtractor::TagMatchExtractor()
{
}

double TagMatchExtractor::extract(const OsmMap& /*map*/, const ConstElementPtr& target,
  const ConstElementPtr& candidate) const
{
  QString v1 = target->getTag(_key);
  QString v2 = candidate->getTag(_key);
  if (v1 == v2 && !v1.isEmpty())
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

QString TagMatchExtractor::getDescription() const
{
  return "Extracts 1 if both features have a matching value for key";
}

QString TagMatchExtractor::getName() const
{
  return QString("TagMatchExtractor %1").arg(_key);
}

}
