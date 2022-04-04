/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/scoring/DataSamples.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

static void init_DataSamples(py::module_& m)
{
  auto wrapme =
    py::class_<DataSamples, std::shared_ptr<DataSamples> >
      (m, "DataSamples")
      .def("getUniqueLabels", &DataSamples::getUniqueLabels)
      .def("toDataFrame", &DataSamples::toDataFrame)
      .def("get", &DataSamples::get)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_DataSamples)

}
