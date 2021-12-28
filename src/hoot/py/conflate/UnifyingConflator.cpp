/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/UnifyingConflator.h>
#include <hoot/core/io/OsmJsonWriter.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;
using namespace std;

namespace hoot
{

static void init_UnifyingConflator(py::module_& m)
{
  auto wrapme = py::class_<hoot::UnifyingConflator>(m, "UnifyingConflator")
    .def(py::init<>())
    //.def(py::init<const std::shared_ptr<MatchThreshold>&>())
    .def("apply", &UnifyingConflator::apply, R"TOK(
apply conflates the specified map.

If the map is not in a planar projection it is reprojected. The map is not reprojected back to
the original projection when conflation is complete.
@see OsmMapOperation
)TOK")
    .def("getName", &UnifyingConflator::getName)
    .def("getClassName", &UnifyingConflator::getClassName)
    .def("getDescription", &UnifyingConflator::getDescription)
    .def("getNumSteps", &UnifyingConflator::getNumSteps)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_UnifyingConflator)

}
