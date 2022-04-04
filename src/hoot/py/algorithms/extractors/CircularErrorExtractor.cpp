/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "CircularErrorExtractor.h"

// hoot
#include <hoot/core/util/Factory.h>
#include <hoot/core/algorithms/string/LevenshteinDistance.h>

using namespace std;

namespace hoot
{

HOOT_FACTORY_REGISTER(FeatureExtractor, CircularErrorExtractor)

CircularErrorExtractor::CircularErrorExtractor(int input) :
  _input(input)
{
  assert(_input == 0 || _input == 1);
}

CircularErrorExtractor::CircularErrorExtractor() :
  _input(0)
{
}

double CircularErrorExtractor::extract(const OsmMap& /*map*/, const ConstElementPtr& target,
  const ConstElementPtr& candidate) const
{
  if (_input == 0)
  {
    return extract(target);
  }
  else
  {
    return extract(candidate);
  }
}

double CircularErrorExtractor::extract(const ConstElementPtr& element) const
{
  return element->getCircularError();
}

QString CircularErrorExtractor::getName() const
{
  return QString("CircularErrorExtractor %1").arg(_input);
}

}
