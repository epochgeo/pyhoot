/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "StatusEqualsExtractor.h"

// hoot
#include <hoot/core/util/Factory.h>
#include <hoot/core/algorithms/string/LevenshteinDistance.h>

using namespace std;

namespace hoot
{

HOOT_FACTORY_REGISTER(FeatureExtractor, StatusEqualsExtractor)

StatusEqualsExtractor::StatusEqualsExtractor(Status status) :
  _status(status)
{
}

StatusEqualsExtractor::StatusEqualsExtractor() :
  _status(Status::Invalid)
{
}

double StatusEqualsExtractor::extract(const OsmMap& /*map*/, const ConstElementPtr& target,
  const ConstElementPtr& candidate) const
{
  if (target->getStatus() == _status &&
    candidate->getStatus() == _status)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

QString StatusEqualsExtractor::getName() const
{
  return QString("StatusEqualsExtractor %1").arg(_status.toString());
}

}
