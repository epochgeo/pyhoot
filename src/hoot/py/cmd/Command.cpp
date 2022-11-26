/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 *
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2016, 2017, 2018, 2019, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/cmd/Command.h>
#include <hoot/core/util/Factory.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

// qt
#include <QVector>

namespace py = pybind11;

using namespace std;

namespace hoot
{

int RunCommand(QString cmd, QStringList args)
{
  LOG_VARD(cmd);
  LOG_VARD(args);

  vector<QString> cmds = Factory::getInstance().getObjectNamesByBase(Command::className());
  std::shared_ptr<Command> command;
  for (size_t i = 0; i < cmds.size(); i++)
  {
    command = Factory::getInstance().constructObject<Command>(cmds[i]);
    QString argName = command->getName();
    if (cmd == argName)
    {
      break;
    }
    else
    {
      command.reset();
    }
  }

  // convert arguments to UTF-8 char*
  // we keep the QByteArray around so the contents don't become invalidated during the call to
  // command->run
  QList<QByteArray> argsBytes;
  for (auto arg : args)
  {
    argsBytes.append(arg.toUtf8());
  }
  vector<char*> argv;
  QByteArray cmdBytes = cmd.toUtf8();

  // we know this won't be modified
  argv.push_back((char*)"hoot");
  argv.push_back(cmdBytes.data());
  QStringList tmp;
  for (int i = 0; i < args.size(); i++)
  {
    argv.push_back(argsBytes[i].data());
  }

  int result;
  if (command != nullptr)
  {
    result = command->run(argv.data(), argv.size());
  }
  else
  {
    // Calls to HelpCmd won't work b/c we're not building the hoot-cmd library which it is in.
    command = Factory::getInstance().constructObject<Command>("HelpCmd");
    command->run(argv.data(), argv.size());
    result = -1;
  }

  return result;
}

void init_Command(py::module_& m)
{
  auto wrapme = py::class_<hoot::Command>(m, "Command")
    .def_static("run", &RunCommand, R"(
run will run a hootenanny command line command within the current runtime.

Example:
    An example conflation command that is equivalent to running the hoot command line
    "python -m hoot conflate $HOOT_HOME/ToyTestA.osm $HOOT_HOME/ToyTestB.osm output.osm"

        hoot.Command.run("conflate", [hoot.TOY_TEST_A_PATH, hoot.TOY_TEST_B_PATH, "output.osm"])
)")
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_Command)

}
