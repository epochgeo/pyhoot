/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/TestUtils.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

using namespace std;

void init_TestUtils(py::module_& m)
{
  auto wrapme = py::class_<TestUtils, unique_ptr<TestUtils, py::nodelete> >(m, "TestUtils")
    .def(py::init([]() { return TestUtils::getInstance(); }),
      R"TOK(
Return the singleton instance.
)TOK")
    .def("registerReset", &TestUtils::registerReset, R"TOK(
Register a way to reset the environment. This is most useful in plugins to avoid circular
references.
)TOK")
    .def_static ("resetBasic", &TestUtils::resetBasic, R"TOK(
Resets the test environment including counters, keys, and seeds
)TOK")
    .def_static ("toQuotedString", &TestUtils::toQuotedString, R"TOK(
Converts a string into a format that can be cut/paste into c++ code.
)TOK")
    .def_static ("resetConfigs", &TestUtils::resetConfigs, R"TOK(
resetConfigs Reset the configuration from the default, Testing.conf, and input files
:param confs: custom config files to load during reset; if left blank the default config
  in ConfigOptions will be loaded
)TOK",
      py::arg("confs") = QStringList())
    .def_static ("resetEnvironment", &TestUtils::resetEnvironment, R"TOK(
resetEnvironment Resets the test environment to a known state.
:param confs: custom confs to load during reset; if left blank the default config in
  ConfigOptions will be loaded
)TOK",
      py::arg("confs") = QStringList())
    .def_static ("resetAll", &TestUtils::resetAll, R"TOK(
resetAll Resets the test environment and including the MatchFactory
:param confs: custom confs to load during reset; if left blank the default config in
  ConfigOptions will be loaded
)TOK",
      py::arg("confs") = QStringList())
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_TestUtils)

}
