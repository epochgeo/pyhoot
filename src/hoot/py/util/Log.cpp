/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
// ugh
#define private public
#include <hoot/core/util/Log.h>
#undef private

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

static void init_Log(py::module_& m)
{
  auto log = py::class_<Log, std::unique_ptr<Log, py::nodelete> >(m, "Log")
    .def_static("getInstance", []() {
      return std::unique_ptr<Log, py::nodelete>(&Log::getInstance());
    })
    .def_static ("bad_string", []() {
      unsigned char result[] = {0x4d, 0x41, 0x4b, 0x53, 0x5c, 0x75, 0x64, 0x38, 0x33, 0x64, 0x5c, 0x75, 0x64, 0x63, 0x39, 0x65, 0x5c, 0x75, 0x64, 0x38, 0x33, 0x64, 0x5c, 0x75, 0x64, 0x63, 0x39, 0x65, 0x00};
      return QString::fromUtf8((const char*)result);
    })
    .def_static ("levelFromString", &Log::levelFromString)
    .def_static ("levelToString", &Log::levelToString)
    .def("getLevelAsString", &Log::getLevelAsString)
    .def("isDebugEnabled", &Log::isDebugEnabled)
    .def("isInfoEnabled", &Log::isInfoEnabled)
    .def_static("log", [](Log::WarningLevel level, std::string msg) { Log::getInstance().log(level, msg); })
    .def_static("log", [](Log::WarningLevel level, std::string msg, std::string filename,
      std::string functionName, int lineNumber) {
      Log::getInstance().log(level, msg, filename, functionName, lineNumber);
    })
    .def("progress", &Log::progress)
    .def_static ("getWarnMessageLimit", &Log::getWarnMessageLimit)
    .def("getLevel", &Log::getLevel)
    .def("setLevel", &Log::setLevel)
    .def("setDecorateLogs", &Log::setDecorateLogs)
  ;
  PyBindModule::remapNames(log);

  py::enum_<hoot::Log::WarningLevel>(log, "WarningLevel")
    .value("NONE", Log::WarningLevel::None)
    .value("TRACE", Log::WarningLevel::Trace)
    .value("DEBUG", Log::WarningLevel::Debug)
    .value("INFO", Log::WarningLevel::Info)
    .value("STATUS", Log::WarningLevel::Status)
    .value("WARN", Log::WarningLevel::Warn)
    .value("ERROR", Log::WarningLevel::Error)
    .value("FATAL", Log::WarningLevel::Fatal)
    .export_values();
}

REGISTER_PYHOOT_SUBMODULE(init_Log)

}
