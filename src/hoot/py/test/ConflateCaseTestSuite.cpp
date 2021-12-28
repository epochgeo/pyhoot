/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// CPP Unit
#include <cppunit/Exception.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

// hoot
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/util/ConfigOptions.h>
#include <hoot/core/util/ConfPath.h>
#include <hoot/test/ConflateCaseTestSuite.h>

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/test/PyHootTestListener.h>

namespace py = pybind11;
using namespace std;

namespace hoot
{

using TestPtr = shared_ptr<CppUnit::Test>;

void getTestVector(CppUnit::Test* from, vector<CppUnit::Test*>& to)
{
  for (int i = 0; i < from->getChildTestCount(); i++)
  {
    CppUnit::Test* child = from->getChildTestAt(i);
    if (dynamic_cast<CppUnit::TestComposite*>(child))
      getTestVector(child, to);
    else
      to.push_back(child);
  }
}

void getTestVector(const vector<TestPtr>& from, vector<CppUnit::Test*>& to)
{
  for (const auto& test : from)
  {
    CppUnit::Test* child = test.get();
    if (dynamic_cast<CppUnit::TestComposite*>(child))
      getTestVector(child, to);
    else
      to.push_back(child);
  }
}

bool runDir(QString path)
{
  auto listener = std::make_shared<PyHootTestListener>(false, false);
  conf().set(ConfigOptions().getHashSeedZeroKey(), true);
  qSetGlobalQHashSeed(0);
  conf().loadJson(ConfPath::search("Testing.conf"));

  std::vector<TestPtr> vAllTests;
  std::vector<CppUnit::Test*> vTestsToRun;
  CppUnit::TextTestResult result;

  vAllTests.push_back(make_shared<ConflateCaseTestSuite>(path, false, true, true));

  getTestVector(vAllTests, vTestsToRun);

  result.addListener(listener.get());

  // run all tests
  for (size_t i = 0; i < vTestsToRun.size(); i++)
  {
    OsmMap::resetCounters();
    vTestsToRun[i]->run(&result);
  }

  return result.failures().size() == 0;
}

void init_ConflateCaseTestSuite(py::module_& m)
{
  auto wrapme = py::class_<ConflateCaseTestSuite, std::shared_ptr<ConflateCaseTestSuite> >
    (m, "ConflateCaseTestSuite")
    .def_static("run_dir", &runDir)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_ConflateCaseTestSuite)

}
