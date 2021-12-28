/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/info/Version.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

static void init_Version(py::module_& m)
{
  auto wrapme = py::class_<Version>(m, "Version")
    .def_static("getBuiltBy", &Version::getBuiltBy)
    .def_static("getFullVersion", &Version::getFullVersion)
    .def_static("getRevision", &Version::getRevision)
    .def_static("getVersion", &Version::getVersion)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_Version)

}
