/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/ops/MapCleaner.h>
#include <hoot/core/ops/RecursiveElementRemover.h>
#include <hoot/core/ops/ReplaceElementOp.h>
#include <hoot/core/ops/SuperfluousNodeRemover.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

namespace hoot
{

static void init_ConstOsmMapOperation(py::module_& m)
{
  auto constOsmMapOperation = py::class_<ConstOsmMapOperation>(m, "ConstOsmMapOperation")
    .def("apply", [](ConstOsmMapOperation& self, const OsmMapPtr& map) {
      self.apply(map);
    })
  ;
  PyBindModule::remapNames(constOsmMapOperation);

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
