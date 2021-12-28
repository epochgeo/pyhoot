/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/ConflateExecutor.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

// qt
#include <QSet>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_ConflateExecutor(py::module_& m)
{
  auto executor = py::class_<hoot::ConflateExecutor>(m, "ConflateExecutor")
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
  PyBindModule::remapNames(executor);
}

REGISTER_PYHOOT_SUBMODULE(init_ConflateExecutor)

}
