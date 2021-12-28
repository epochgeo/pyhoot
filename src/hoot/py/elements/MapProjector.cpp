/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/elements/MapProjector.h>
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

using OsmMapPtr = std::shared_ptr<OsmMap>;

void init_MapProjector(py::module_& m)
{
  auto wrapme = py::class_<MapProjector, std::unique_ptr<MapProjector, py::nodelete> >
    (m, "MapProjector")
    .def_static("projectToPlanar",
      [](const OsmMapPtr& map) { MapProjector::projectToPlanar(map); },
R"TOK(
Uses createPlanarProjection to create a planar projection and then reprojects the given map.
Uses the envelope of the map to determine the projection.
)TOK")
    .def_static("projectToWgs84", &MapProjector::projectToWgs84)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_MapProjector)

}
