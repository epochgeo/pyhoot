/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/elements/ElementType.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

void init_ElementType(py::module_& m)
{
  auto elementType = py::class_<ElementType>(m, "ElementType")
    .def(py::init<>())
    .def(py::init<ElementType::Type>())
    .def("__eq__", [](ElementType& self, ElementType& other) { return self == other; })
    .def("__eq__", [](ElementType& self, ElementType::Type& other) { return self == other; })
    .def("__str__", &ElementType::toString)
    .def("getEnum", &ElementType::getEnum)
    .def_static("isValidTypeString", &ElementType::isValidTypeString)
    .def_static("fromString", &ElementType::fromString);

  py::enum_<hoot::ElementType::Type>(elementType, "Type")
    .value("NODE", ElementType::Type::Node)
    .value("WAY", ElementType::Type::Way)
    .value("RELATION", ElementType::Type::Relation)
    .value("UNKNOWN", ElementType::Type::Unknown)
    .export_values();
  // do not wrap
  //PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_ElementType)

}
