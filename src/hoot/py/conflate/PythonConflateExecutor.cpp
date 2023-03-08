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
#include "PythonConflateExecutor.h"

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

using namespace hoot;
using namespace std;

namespace hoot
{

void PythonConflateExecutor::_runConflatePreOps(OsmMapPtr map)
{
  ConflateExecutor::_runConflatePreOps(map);

  for (auto iterator = _preOps.begin(); iterator != _preOps.end(); ++iterator)
  {
    PyMapOpFunction function = *iterator;
    function(map);
  }
}

void PythonConflateExecutor::_runConflatePostOps(OsmMapPtr map)
{
  ConflateExecutor::_runConflatePostOps(map);

  for (auto iterator = _postOps.begin(); iterator != _postOps.end(); ++iterator)
  {
    PyMapOpFunction function = *iterator;
    function(map);
  }
}

}
