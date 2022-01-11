/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/util/Settings.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_Settings(py::module_& m)
{
  auto wrapme = py::class_<Settings, std::unique_ptr<Settings, py::nodelete> >
    (m, "Settings")
    .def_static("getInstance", []() {
      return std::unique_ptr<Settings, py::nodelete>(&Settings::getInstance());
    })
    .def("__getitem__", [](const Settings& self, QString key) { return self.getString(key); })
    .def("__setitem__", [](Settings& self, QString k, QString v) { return self.set(k, v); })
    .def("__setitem__", [](Settings& self, QString k, double v) { return self.set(k, v); })
    .def("__setitem__", [](Settings& self, QString k, int v) { return self.set(k, v); })
    .def("__setitem__", [](Settings& self, QString k, bool v) { return self.set(k, v); })
    .def("get", [](const Settings& self, QString key) { return self.getString(key); })
    .def("getDouble", [](const Settings& self, QString key) {
      return self.getDouble(key);
    })
    .def("getDouble", [](const Settings& self, QString key, double defaultValue) {
      return self.getDouble(key, defaultValue);
    })
    .def("set", [](Settings& self, QString k, QString v) { return self.set(k, v); })
    .def("set", [](Settings& self, QString k, double v) { return self.set(k, v); })
    .def("set", [](Settings& self, QString k, int v) { return self.set(k, v); })
    .def("set", [](Settings& self, QString k, bool v) { return self.set(k, v); })
  ;

  PyBindModule::remapNames(wrapme);

  m.def("conf", []() {
      return std::unique_ptr<Settings, py::nodelete>(&Settings::getInstance());
    },
    "conf is a shortcut for Settings.get_instance()");
}

REGISTER_PYHOOT_SUBMODULE(init_Settings)

}
