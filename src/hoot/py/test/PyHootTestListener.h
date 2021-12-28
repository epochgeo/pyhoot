/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 *
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#ifndef PYHOOTTESTLISTENER_H
#define PYHOOTTESTLISTENER_H

// standard
#include <iostream>

// tgs
#include <tgs/System/Time.h>

namespace hoot
{

using namespace std;

/**
 * PyHootTestListener is a direct rip off of the test listener from HootTest.
 */
class PyHootTestListener : public CppUnit::TestListener
{
public:

  PyHootTestListener(bool showTestName, bool suppressFailureDetail = false,
                   double testTimeout = 5, bool showElapsed = true)
    : _success(true),
      _showTestName(showTestName),
      _suppressFailureDetail(suppressFailureDetail),
      _showElapsed(showElapsed),
      _start(Tgs::Time::getTime()),
      _allStart(_start),
      _testTimeout(testTimeout)
  {
  }

  void addFailure(const CppUnit::TestFailure& failure) override
  {
    cout << endl << "Failure: " << failure.failedTest()->getName() << endl;
    if (!_suppressFailureDetail)
    {
      cout << "  " << failure.sourceLine().fileName() << "("
           << failure.sourceLine().lineNumber() << ") ";
      CppUnit::Exception* e = failure.thrownException();
      if (e != nullptr && QString::fromStdString(e->message().details()).trimmed() != "")
        cout << "  " << e->message().details();
    }
    cout.flush();
    _success = false;
  }

  bool getSuccess() const
  {
    return _success;
  }

  void endTest(CppUnit::Test* test) override
  {
    double elapsed = Tgs::Time::getTime() - _start;
    if (_showTestName)
      cout << test->getName() << " - " << elapsed << endl;
    if (elapsed > _testTimeout && _testTimeout >= 0.0)
    {
      cout << "Test " << test->getName().data() << " ran longer than expected -- "
           << elapsed << endl;
    }
    cout.flush();

    _start = Tgs::Time::getTime();
  }

  void showTestNames(bool show) { _showTestName = show; }

  void startSuite(CppUnit::Test* suite) override
  {
    if (_showTestName)
      cout << "Starting " << suite->getName().data() << endl << flush;
  }

  void endTestRun(CppUnit::Test* /*test*/, CppUnit::TestResult* /*eventManager*/) override
  {
    if (_showElapsed)
      cout << endl << "Elapsed: " << Tgs::Time::getTime() - _allStart << endl;
  }

  double getTestTimeout() const { return _testTimeout; }

private:

  bool _success;
  bool _showTestName;
  bool _suppressFailureDetail;
  bool _showElapsed;

  double _start;
  double _allStart;
  double _testTimeout;
};

}

#endif // PYHOOTTESTLISTENER_H
