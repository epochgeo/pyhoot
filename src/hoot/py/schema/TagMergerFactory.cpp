/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Qt
#include <QSet>

// hoot
#include <hoot/core/schema/TagMerger.h>
#include <hoot/core/schema/TagMergerFactory.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_TagMergerFactory(py::module_& m)
{
  auto wrapme = py::class_<hoot::TagMergerFactory,
    std::unique_ptr<TagMergerFactory, py::nodelete> >
    (m, "TagMergerFactory")
    .def(py::init([]() { return &TagMergerFactory::getInstance(); }))
    .def_static("getInstance", []() { return &TagMergerFactory::getInstance(); })
    .def("getDefault", &TagMergerFactory::getDefaultPtr, R"TOK(
Returns the default TagMerger.
)TOK")
    .def("getMerger", &TagMergerFactory::getMergerPtr)
    .def_static ("mergeTags", &TagMergerFactory::mergeTags, R"TOK(
A convenience function for merging tags using the default mechanism. Equivalent to:
TagMergerFactory::getInstance().getDefault().mergeTags(t1, t2, et);
)TOK")
    .def_static ("mergeTags",
      [](Tags t1, Tags t2) {
        return TagMergerFactory::mergeTags(t1, t2, ElementType::Unknown);
      }, R"TOK(
A convenience function for merging tags using the default mechanism. Equivalent to:
TagMergerFactory::getInstance().getDefault().mergeTags(t1, t2, ElementType::Unknown);
)TOK")
    .def("reset", &TagMergerFactory::reset, R"TOK(
Reset all cached information. This is necessary if the default tag config information changes.
)TOK")
    .def("toString", &TagMergerFactory::toString, R"TOK(
Return the list of mergers as a string
)TOK")
    .def("__str__", &TagMergerFactory::toString)
;

     PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_TagMergerFactory)

}
