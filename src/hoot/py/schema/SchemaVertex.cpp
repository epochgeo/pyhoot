/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/elements/Tags.h>
#include <hoot/core/schema/SchemaVertex.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

using SchemaVertexPtr = std::shared_ptr<SchemaVertex>;

void init_SchemaVertex(py::module_& m)
{
  auto wrapme = py::class_<SchemaVertex, std::shared_ptr<SchemaVertex> >(m, "SchemaVertex")
    .def(py::init([]() { return SchemaVertexPtr(new SchemaVertex()); }))
    .def("__str__", &SchemaVertex::toString)
    .def("addCompoundRule", &SchemaVertex::addCompoundRule, R"TOK(
Add a compound rule. This must be a "Compound" type to be valid.
)TOK")
    .def("isCompoundMatch", &SchemaVertex::isCompoundMatch, R"TOK(
Returns true if one or more of the compound rules match this tag.
)TOK")
    .def("isEmpty", &SchemaVertex::isEmpty)
    .def_static ("isMatch", &SchemaVertex::isMatch, R"TOK(
Returns true if each of the elements in this rule matches one of the kvps in t.
)TOK")
    .def("isValid", &SchemaVertex::isValid)
    .def("getType", &SchemaVertex::getType)
    .def("getCompoundRules", &SchemaVertex::getCompoundRules, R"TOK(
Yes, technically you could modify the contents of the rules returned. Please don't. Taking
this short cut we don't need to copy the rules into a proper const object each time.
)TOK")
    .def("getName", &SchemaVertex::getName)
    .def("getDescription", &SchemaVertex::getDescription)
    .def("getKey", &SchemaVertex::getKey)
    .def("getValue", &SchemaVertex::getValue)
    .def("getInfluence", &SchemaVertex::getInfluence)
    .def("getChildWeight", &SchemaVertex::getChildWeight)
    .def("getMismatchScore", &SchemaVertex::getMismatchScore)
    .def("getValueType", &SchemaVertex::getValueType)
    .def("getAliases", &SchemaVertex::getAliases)
    .def("getCategories", &SchemaVertex::getCategories)
    .def("getGeometries", &SchemaVertex::getGeometries)
    .def("setName", &SchemaVertex::setName, R"TOK(
Sets the name and does not parse out the key/value. The key and value will not be changed.
)TOK")
    .def("setDescription", &SchemaVertex::setDescription)
    .def("setNameKvp", &SchemaVertex::setNameKvp, R"TOK(
Sets the name and parses out and stores the key/value.
)TOK")
    .def("setType", &SchemaVertex::setType)
    .def("setValueTypeString", &SchemaVertex::setValueTypeString)
    .def("setKey", &SchemaVertex::setKey)
    .def("setValue", &SchemaVertex::setValue)
    .def("setInfluence", &SchemaVertex::setInfluence)
    .def("setChildWeight", &SchemaVertex::setChildWeight)
    .def("setMismatchScore", &SchemaVertex::setMismatchScore)
    .def("setValueType", &SchemaVertex::setValueType)
    .def("setAliases", &SchemaVertex::setAliases)
    .def("setCategories", &SchemaVertex::setCategories)
    .def("addCategory", &SchemaVertex::addCategory)
    .def("setGeometries", &SchemaVertex::setGeometries)
    .def("toString", &SchemaVertex::toString)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_SchemaVertex)

}
