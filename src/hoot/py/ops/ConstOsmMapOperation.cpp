/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
//#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/ops/MapCleaner.h>
//#include <hoot/core/ops/ConstOsmMapOperation.h>
#include <hoot/core/ops/RecursiveElementRemover.h>
#include <hoot/core/ops/ReplaceElementOp.h>
#include <hoot/core/ops/SuperfluousNodeRemover.h>

// pybind11
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

using namespace hoot;
using namespace std;

namespace hoot
{

using PyMapOpFunction = std::function<void(const std::shared_ptr<OsmMap>& map)>;

class ConstOsmMapOperationPy : public ConstOsmMapOperation
{
public:

  static QString className() { return "ConstOsmMapOperationPy"; }

  ConstOsmMapOperationPy() = default;
  ~ConstOsmMapOperationPy() = default;

  /**
   * @see ConstOsmMapOperation
   */
  void apply(const std::shared_ptr<OsmMap>& map) override
  {
    _func(map);
  }

  QString getDescription() const override
  { return "Runs a custom python map operation"; }
  QString getName() const override { return className(); }
  QString getClassName() const override { return className(); }

  PyMapOpFunction getFunction() { return _func; }
  void setFunction(PyMapOpFunction func) { _func = func; }

private:

  PyMapOpFunction _func;
};

static void init_ConstOsmMapOperation(py::module_& m)
{
  auto constOsmMapOperation = py::class_<ConstOsmMapOperation>(m, "ConstOsmMapOperation")
    .def("apply", [](ConstOsmMapOperation& self, const OsmMapPtr& map) {
      self.apply(map);
    })
  ;
  PyBindModule::remapNames(constOsmMapOperation);

  auto wrapme = py::class_<ConstOsmMapOperationPy, shared_ptr<ConstOsmMapOperationPy> >
      (m, "ConstOsmMapOperationPy", constOsmMapOperation)
      .def(py::init<>())
      .def_property("function",
        &ConstOsmMapOperationPy::getFunction,
        &ConstOsmMapOperationPy::setFunction, R"TOK(
  function is the user defined function that will be called for all elements. Elements can be
  modified directly by the user function.
  )TOK")
    ;
    PyBindModule::remapNames(wrapme);

  auto recursiveElementRemover = py::class_<RecursiveElementRemover,
    std::shared_ptr<RecursiveElementRemover> >
      (m, "RecursiveElementRemover", constOsmMapOperation)
    .def(py::init([](ElementId eid) { return new RecursiveElementRemover(eid); }))
  ;
  PyBindModule::remapNames(recursiveElementRemover);

  auto replaceElementOp = py::class_<ReplaceElementOp, std::shared_ptr<ReplaceElementOp> >
      (m, "ReplaceElementOp", constOsmMapOperation)
    .def(py::init([](ElementId eid1, ElementId eid2) { return new ReplaceElementOp(eid1, eid2); }))
  ;
  PyBindModule::remapNames(replaceElementOp);

  registerClass<SuperfluousNodeRemover>(m);
  registerClass<MapCleaner>(m);
}

REGISTER_PYHOOT_SUBMODULE(init_ConstOsmMapOperation)

}
