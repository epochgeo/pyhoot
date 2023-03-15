/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/ConflateExecutor.h>
#include <hoot/core/elements/OsmMap.h>

// pybind11
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

// qt
#include <QSet>

namespace py = pybind11;

using namespace hoot;
using namespace std;

namespace hoot
{

using PyMapOpFunction = std::function<void(std::shared_ptr<OsmMap>& map)>;

class PythonConflateExecutor : public ConflateExecutor
{
public:

  static QString className() { return "PythonConflateExecutor"; }

  PythonConflateExecutor() = default;
  ~PythonConflateExecutor() = default;

  std::vector<PyMapOpFunction> getPreOps() { return _preOps; }
  void setPreOps(std::vector<PyMapOpFunction> preOps) { _preOps = preOps; }

  std::vector<string> getPreOpNames() { return _preOpNames; }
  void setPreOpNames(std::vector<std::string> preOpNames) { _preOpNames = preOpNames; }

  std::vector<PyMapOpFunction> getPostOps() { return _postOps; }
  void setPostOps(std::vector<PyMapOpFunction> postOps) { _postOps = postOps; }

  std::vector<string> getPostOpNames() { return _postOpNames; }
  void setPostOpNames(std::vector<std::string> postOpNames) { _postOpNames = postOpNames; }

protected:

  void _runConflatePreOps(OsmMapPtr map) override
  {
    ConflateExecutor::_runConflatePreOps(map);

    for (int i = 0; i < _preOps.size(); i++)
    {
      PyMapOpFunction function = _preOps.at(i);
      std::string op_name = _preOpNames.at(i);
      LOG_STATUS("Executing " + op_name + "...");
      function(map);
    }
  }

  void _runConflatePostOps(OsmMapPtr map) override
  {
    ConflateExecutor::_runConflatePostOps(map);

    for (int i = 0; i < _postOps.size(); i++)
    {
      PyMapOpFunction function = _postOps.at(i);
      std::string op_name = _postOpNames.at(i);
      LOG_STATUS("Executing " + op_name + "...");
      function(map);
    }
  }

private:

  std::vector<PyMapOpFunction> _preOps;
  std::vector<std::string> _preOpNames;
  std::vector<PyMapOpFunction> _postOps;
  std::vector<std::string> _postOpNames;
};

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
      .def_property("preOpNames",
        &PythonConflateExecutor::getPreOpNames,
        &PythonConflateExecutor::setPreOpNames)
      .def_property("postOps",
        &PythonConflateExecutor::getPostOps,
        &PythonConflateExecutor::setPostOps, R"TOK(
  function is the user defined function that will be called for all elements. Elements can be
  modified directly by the user function.
  )TOK")
      .def_property("postOpNames",
        &PythonConflateExecutor::getPostOpNames,
        &PythonConflateExecutor::setPostOpNames)
    ;
  PyBindModule::remapNames(pythonConflateExecutor);
}

REGISTER_PYHOOT_SUBMODULE(init_ConflateExecutor)

}
