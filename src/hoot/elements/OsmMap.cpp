/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/elements/OsmMap.h>

#include <hoot/bindings/QtBindings.h>
#include <hoot/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace pyhoot
{

void init_OsmMap(py::module_& m)
{
    auto osmMap = py::class_<hoot::OsmMap, std::shared_ptr<OsmMap> >(m, "OsmMap")
        .def(py::init([]() { return OsmMapPtr(new OsmMap()); }))
        .def("getElement",
            static_cast<ElementPtr (OsmMap::*)(const ElementId&)>(&OsmMap::getElement),
            "getElement returns an element by ElementId")
        .def("getElement",
            static_cast<ElementPtr (OsmMap::*)(ElementType type, long id)>(&OsmMap::getElement),
            "getElement returns an element by element type and id")
        .def("size", &OsmMap::size, "size returns the number of elements");
    PyBindModule::remapNames(osmMap);
}

REGISTER_PYHOOT_SUBMODULE(init_OsmMap)

}
