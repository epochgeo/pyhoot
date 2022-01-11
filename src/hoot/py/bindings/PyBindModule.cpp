/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include "PyBindModule.h"

// hoot
#include <hoot/core/Hoot.h>
#include <hoot/core/util/Log.h>
#include <hoot/core/util/SignalCatcher.h>
#include <hoot/js/HootJsStable.h>
#include <hoot/js/JsRegistrar.h>
#include <hoot/js/v8Engine.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>

// Qt
#include <QtPlugin>
#include <QRegExp>

// let Qt know that we're using a statically linked plugin
Q_IMPORT_PLUGIN(QSQLiteDriverPlugin)

namespace hoot
{

PYBIND11_MODULE(libpyhoot, m) {
  hoot::Hoot::getInstance();
  hoot::v8Engine::getInstance();
  // register JS functions/classes
  hoot::JsRegistrar::getInstance();
  SignalCatcher::getInstance();

  m.doc() = "Unofficial hootenanny python bindings"; // optional module docstring

  PyBindModule::getInstance().initialize(m);
  
}

PyBindModule& PyBindModule::getInstance()
{
  //  Local static singleton instance
  static PyBindModule instance;
  return instance;
}

void PyBindModule::initialize(py::module_& module)
{
  for (size_t i = 0; i < _initFunctions.size(); i++)
  {
    _initFunctions[i](module);
  }
}

void PyBindModule::registerSubModule(InitSubmoduleFunction func)
{
  _initFunctions.append(func);
}

void PyBindModule::remapNames(py::object classToRename)
{
  // using this later we can convert from camelCase to snake_case.
  QRegExp toSnake("([a-z])([A-Z])");
  py::dict dict = py::cast<py::dict>(classToRename.attr("__dict__"));

  for (auto it : dict)
  {
    QString nameOrig = QString::fromStdString(py::cast<std::string>(it.first));
    QString snake = nameOrig;
    snake.replace(toSnake, "\\1_\\2");
    snake = snake.toLower();
    if (snake != nameOrig)
    {
      // we can't really delete the attribute so just null it.
      classToRename.attr(it.first) = py::none();
      classToRename.attr(py::str(snake.toStdString())) = it.second;
    }
  }
}

}

