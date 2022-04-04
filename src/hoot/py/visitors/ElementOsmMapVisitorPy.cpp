/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/util/Log.h>
#include <hoot/core/visitors/ElementOsmMapVisitor.h>
#include <hoot/core/visitors/RemoveElementsVisitor.h>
#include <hoot/core/visitors/RemoveMissingElementsVisitor.h>

#include <hoot/py/bindings/HootInterfaces.h>
#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

// pybind11
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using namespace hoot;
using namespace std;

namespace hoot
{

using PyElementVisitFunction = std::function<void(const ElementPtr& element)>;

class ElementOsmMapVisitorPy : public ElementOsmMapVisitor
{
public:

  static QString className() { return "ElementOsmMapVisitorPy"; }

  ElementOsmMapVisitorPy() = default;
  ~ElementOsmMapVisitorPy() = default;

  /**
   * @see ElementVisitor
   */
  void visit(const ElementPtr& e) override
  {
    _func(e);
  }

  QString getDescription() const override
  { return "Runs a custom python visitor"; }
  QString getName() const override { return className(); }
  QString getClassName() const override { return className(); }

  PyElementVisitFunction getFunction() { return _func; }
  void setFunction(PyElementVisitFunction func) { _func = func; }

private:
  PyElementVisitFunction _func;

};

void init_ElementOsmMapVisitorPy(py::module_& m)
{
  auto elementVisitor = py::class_<ElementVisitor, shared_ptr<ElementVisitor> >
    (m, "ElementVisitor");

  auto wrapme = py::class_<ElementOsmMapVisitorPy, shared_ptr<ElementOsmMapVisitorPy> >
    (m, "ElementOsmMapVisitorPy", elementVisitor)
    .def(py::init<>())
    .def_property("function",
      &ElementOsmMapVisitorPy::getFunction,
      &ElementOsmMapVisitorPy::setFunction, R"TOK(
function is the user defined function that will be called for all elements. Elements can be
modified directly by the user function.
)TOK")
  ;
  PyBindModule::remapNames(wrapme);

  auto removeElementsVisitor = registerSubclass<RemoveElementsVisitor>(m, elementVisitor)
    .def("setRecursive", &RemoveElementsVisitor::setRecursive)
  ;
  PyBindModule::remapNames(removeElementsVisitor);

  registerSubclass<RemoveMissingElementsVisitor>(m, elementVisitor);
}

REGISTER_PYHOOT_SUBMODULE(init_ElementOsmMapVisitorPy)

}
