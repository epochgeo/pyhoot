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
#ifndef __PYTHON_CONFLATE_EXECUTOR_H__
#define __PYTHON_CONFLATE_EXECUTOR_H__

// hoot
#include <hoot/core/conflate/ConflateExecutor.h>
#include <hoot/core/elements/OsmMap.h>

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

  void _runConflatePreOps(OsmMapPtr map) override;
  void _runConflatePostOps(OsmMapPtr map) override;

private:

  std::vector<PyMapOpFunction> _preOps;
  std::vector<std::string> _preOpNames;
  std::vector<PyMapOpFunction> _postOps;
  std::vector<std::string> _postOpNames;
};

}

#endif // __PYTHON_CONFLATE_EXECUTOR_H__
