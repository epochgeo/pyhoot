/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/elements/ElementId.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

static void init_ElementId(py::module_& m)
{
  auto wrapme = py::class_<ElementId>(m, "ElementId")
    .def(py::init([]() { return ElementId(); }))
    .def(py::init([](QString str) { return ElementId(str); }))
    .def("__hash__", [](const ElementId& self) {
      return qHash(self);
    })
    .def("__lt__", [](const ElementId& self, const ElementId& other) {
      return self < other;
    })
    .def("__eq__", [](const ElementId& self, const ElementId& other) {
      return self == other;
    })
    .def("__ne__", [](const ElementId& self, const ElementId& other) {
      return self != other;
    })
    .def("__repr__", [](const ElementId& self) {
      return QString("ElementId(\"%1\")").arg(self.toString());
    })
    .def("__str__", [](const ElementId& self) { return self.toString(); })
    .def("getId", &ElementId::getId)
    .def("getType", &ElementId::getType)
    .def("toString", [](const ElementId& self) { return self.toString(); })
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_ElementId)

}
