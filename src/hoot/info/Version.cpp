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
#include <hoot/bindings/PyBindModule.h>

namespace py = pybind11;

namespace pyhoot
{

void init_Version(py::module_& m)
{
    auto wrapme = py::class_<hoot::Version>(m, "Version")
        .def_static("getBuiltBy", &hoot::Version::getBuiltBy)
        .def_static("getFullVersion", &hoot::Version::getFullVersion)
        .def_static("getRevision", &hoot::Version::getRevision)
        .def_static("getVersion", &hoot::Version::getVersion)
    ;
    PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_Version)

}
