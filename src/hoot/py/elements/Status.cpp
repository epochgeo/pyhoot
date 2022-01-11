/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/elements/Status.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

void init_Status(py::module_& m)
{
  auto status = py::class_<Status>(m, "Status")
    .def(py::init<>())
    .def(py::init<Status::TypeEnum>())
    .def("__eq__", [](Status& self, Status& other) { return self == other; })
    .def("__eq__", [](Status& self, Status::TypeEnum& other) { return self == other; })
    .def("__str__", &Status::toString)
    .def("getEnum", &Status::getEnum)
    .def("isInput", &Status::isInput, R"TOK(
getInput Unlike the enumeration names and strings, this returns the zero-based number
for the input.
:returns: The zero-based input for this status or throws an exception if this isn't an input.
E.g. Unknown1 returns 0, Unknown2 return 1, etc.
)TOK")
    .def("getInput", &Status::getInput)
    .def("toString", &Status::toString)
    .def("toTextStatus", &Status::toTextStatus, R"TOK(
This is not pretty and it is a copy of "toString".
It is a lot easier to change this when the users want different text output
instead of changing "toString" and all of code, unit tests etc that rely on it.
)TOK")
    .def("isInput", &Status::isInput, R"TOK(
:returns: Returns true if the status is one of any input value (multiary)
)TOK")
    .def("isUnknown", &Status::isUnknown, R"TOK(
isUnknown Provided for backwards compatibility.
:returns: Returns true if the status is one of the first two inputs.
)TOK")
    .def_static ("fromString", &Status::fromString, R"TOK(
fromString Parses type from either a human readable status string or the numeric status
string.
:param statusString: The status string to parse.
:returns: The status parsed or throws an exception if it is an invalid status string.
)TOK")
  ;

  py::enum_<hoot::Status::TypeEnum>(status, "TypeEnum")
    .value("INVALID", Status::TypeEnum::Invalid)
    .value("UNKNOWN1", Status::TypeEnum::Unknown1)
    .value("UNKNOWN2", Status::TypeEnum::Unknown2)
    .value("CONFLATED", Status::TypeEnum::Conflated)
    .value("TAGCHANGE", Status::TypeEnum::TagChange)
    .value("ENUMEND", Status::TypeEnum::EnumEnd)
    .export_values();
  // do not wrap
  //PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_Status)

}
