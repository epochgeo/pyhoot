/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#ifndef __PY_BIND_MODULE__
#define __PY_BIND_MODULE__

// Qt Includes
#include <QList>

#include <pybind11/pybind11.h>

namespace py = pybind11;

// Steps for converting C++ headers to bindings:
//
// Using regex to replace (ignore left ticks):
// ` */\*\*` => `R"`
// ` *\*/` => `"`
// `^ +\* ?` => ``
// `(?s)(R".*?")?\s+(static )?\w+ (\w+).+?\)(const )?;` => `        .def_\2("\3", &Tags::\3, \1);\n`
// `def_\(` => `def\(`
// `, \);` => `\)`
// `@(param \w+)` => `:\1:`
// `@return ` => `:returns: `
// `\n"\);` => `"\);`
// `,R"\s*\n` => `,\nR"`
//
// This is not perfect but it should save some time on large header files.


namespace hoot
{

typedef void (*InitSubmoduleFunction)(py::module_& module);

#pragma GCC visibility push(hidden)
class PyBindModule
{
public:
  /**
   * getInstance is the singleton accessor.
   */
  static PyBindModule& getInstance();

  void initialize(py::module_& module);

  /**
   * registerSubModule should be called for every source file that needs to register Python
   * functions.
   */
  void registerSubModule(InitSubmoduleFunction func);

  /**
   * remapNames remaps camel-case names to snake-case names. If a valid conversion cannot be found
   * the original name is kept.
   */
  static void remapNames(py::object classToRename);

private:
  /** Default constructor/destructor */
  PyBindModule() = default;
  ~PyBindModule() = default;
  /** Delete copy constructor and assignment operator */
  PyBindModule(const PyBindModule&) = delete;
  PyBindModule& operator=(const PyBindModule&) = delete;

  QList<InitSubmoduleFunction> _initFunctions;
};
#pragma GCC visibility pop

class AutoRegisterSubModule
{
public:

  /** 
   * Auto-register a "submodule" to the global modules.
   */
  AutoRegisterSubModule(InitSubmoduleFunction func)
  {
    PyBindModule::getInstance().registerSubModule(func);
  }
};

#define REGISTER_PYHOOT_SUBMODULE(FunctionName)      \
  static hoot::AutoRegisterSubModule FunctionName##AutoRegister(FunctionName);

}

#endif
