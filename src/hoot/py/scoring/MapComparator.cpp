/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/scoring/MapComparator.h>
#include <hoot/core/elements/OsmMap.h>

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

void init_MapComparator(py::module_& m)
{
  auto wrapme = py::class_<MapComparator, std::shared_ptr<MapComparator> >(m, "MapComparator")
    .def(py::init<>())
    .def("isMatch", &MapComparator::isMatch, R"TOK(
Returns true if the maps are essentially the same. Minor differences in node locations are
ignored.
)TOK")
    .def("set_ignore_uuid", &MapComparator::setIgnoreUUID)
    .def("setUseDateTime", &MapComparator::setUseDateTime)
    .def("setErrorLimit", &MapComparator::setErrorLimit)
    .def("setIgnoreTagKeys", &MapComparator::setIgnoreTagKeys)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_MapComparator)

}
