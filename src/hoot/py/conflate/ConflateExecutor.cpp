/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/ConflateExecutor.h>

// pybind11
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/conflate/PythonConflateExecutor.h>

// qt
#include <QSet>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_ConflateExecutor(py::module_& m)
{
  auto conflateExecutor = py::class_<hoot::ConflateExecutor>(m, "ConflateExecutor")
    .def(py::init<>())
    .def("conflate", &ConflateExecutor::conflate, R"(
conflate two inputs and write the conflated data to an output.

:param input1: URL of first map to conflate
:param input2: URL of second map to conflate
:param outputPath; URL to write conflated output
)")
    .def("setIsDiffConflate", &ConflateExecutor::setIsDiffConflate)
    .def("setDiffConflateEnableTags", &ConflateExecutor::setDiffConflateEnableTags)
    .def("setDiffConflateSeparateOutput", &ConflateExecutor::setDiffConflateSeparateOutput)
    .def("setDiffRemoveLinearPartialMatchesAsWhole",
      &ConflateExecutor::setDiffRemoveLinearPartialMatchesAsWhole)
    .def("setDiffRemoveRiverPartialMatchesAsWhole",
      &ConflateExecutor::setDiffRemoveRiverPartialMatchesAsWhole)
    .def("setOsmApiDbUrl", &ConflateExecutor::setOsmApiDbUrl)
    .def("setDisplayStats", &ConflateExecutor::setDisplayStats)
    .def("setOutputStatsFile", &ConflateExecutor::setOutputStatsFile)
    .def("setDisplayChangesetStats", &ConflateExecutor::setDisplayChangesetStats)
    .def("setOutputChangesetStatsFile", &ConflateExecutor::setOutputChangesetStatsFile)
  ;
  PyBindModule::remapNames(conflateExecutor);

  auto pythonConflateExecutor = py::class_<PythonConflateExecutor, shared_ptr<PythonConflateExecutor> >
      (m, "PythonConflateExecutor", conflateExecutor)
      .def(py::init<>())
      .def_property("preOps",
        &PythonConflateExecutor::getPreOps,
        &PythonConflateExecutor::setPreOps, R"TOK(
  function is the user defined function that will be called for all elements. Elements can be
  modified directly by the user function.
  )TOK")
   .def_property("postOps",
        &PythonConflateExecutor::getPostOps,
        &PythonConflateExecutor::setPostOps, R"TOK(
  function is the user defined function that will be called for all elements. Elements can be
  modified directly by the user function.
  )TOK")
    ;
  PyBindModule::remapNames(pythonConflateExecutor);
}

REGISTER_PYHOOT_SUBMODULE(init_ConflateExecutor)

}
