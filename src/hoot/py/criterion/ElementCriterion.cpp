/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <hoot/core/criterion/AreaCriterion.h>
#include <hoot/core/criterion/ElementCriterion.h>
#include <hoot/core/criterion/HasNameCriterion.h>
#include <hoot/core/criterion/LinearCriterion.h>
#include <hoot/core/criterion/NodeCriterion.h>
#include <hoot/core/criterion/NotCriterion.h>
#include <hoot/core/criterion/NoInformationCriterion.h>
#include <hoot/core/criterion/OrCriterion.h>
#include <hoot/core/criterion/PoiCriterion.h>
#include <hoot/core/criterion/PointCriterion.h>
#include <hoot/core/criterion/PolygonCriterion.h>
#include <hoot/core/criterion/StatusCriterion.h>
#include <hoot/core/criterion/TagCriterion.h>
#include <hoot/core/criterion/TagKeyCriterion.h>
#include <hoot/core/criterion/WayNodeCriterion.h>

#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

namespace hoot
{

using namespace std;

void init_ElementCriterion(py::module_& m)
{
  auto wrapme = py::class_<ElementCriterion, std::shared_ptr<ElementCriterion> >
    (m, "ElementCriterion")
    .def("__str__", &ElementCriterion::toString)
    .def("isSatisfied", &ElementCriterion::isSatisfied)
    .def("isSatisfied", [](const ElementCriterion& self,
        const vector<ConstElementPtr>& elements) {
        // return a numpy array
        auto result = py::array_t<bool>(elements.size());
        bool* resultPtr = static_cast<bool*>(result.request().ptr);
        for (size_t i = 0; i < elements.size(); i++)
        {
          resultPtr[i] = self.isSatisfied(elements[i]);
        }
        return result;
    }, R"TOK(
This override to the isSatisfied function is pyhoot specific and allows you to calculate
satisfaction on an array of values in one pass.

Returns:
    a boolean numpy array
)TOK")
    .def("clone", &ElementCriterion::clone)
    .def("toString", &ElementCriterion::toString)
  ;

  PyBindModule::remapNames(wrapme);

  registerSubclass<AreaCriterion>(m, wrapme);
  registerSubclass<HasNameCriterion>(m, wrapme);
  registerSubclass<LinearCriterion>(m, wrapme);
  registerSubclass<NodeCriterion>(m, wrapme);
  registerSubclass<NotCriterion>(m, wrapme)
    .def(py::init([](ElementCriterionPtr e) { return make_shared<NotCriterion>(e); }))
  ;
  registerSubclass<NoInformationCriterion>(m, wrapme);
  registerSubclass<PoiCriterion>(m, wrapme);
  registerSubclass<PointCriterion>(m, wrapme);
  registerSubclass<PolygonCriterion>(m, wrapme);
  auto statusCrit = registerSubclass<StatusCriterion>(m, wrapme);
  statusCrit.def(py::init([](Status status)
  {
    return make_shared<StatusCriterion>(status);
  }));
  auto tagCrit = registerSubclass<TagCriterion>(m, wrapme);
  tagCrit.def(py::init([](QString key, QString value)
  {
    return make_shared<TagCriterion>(key, value);
  }));
  auto tagKeyCrit = registerSubclass<TagKeyCriterion>(m, wrapme);
  tagKeyCrit.def(py::init([](QString key) { return make_shared<TagKeyCriterion>(key); }));
  auto chainCrit = registerSubclass<ChainCriterion>(m, wrapme);
  // don't call registerSubclass here or we'll register some interfaces twice
  auto orCrit = py::class_<OrCriterion, std::shared_ptr<OrCriterion> >
    (m, "OrCriterion", chainCrit)
    .def(py::init([](py::args args) {
      auto result = make_shared<OrCriterion>();
      for (auto arg : args)
      {
        auto crit = py::cast<ElementCriterionPtr>(arg);
        result->addCriterion(crit);
      }
      return result;
    }))
  ;
  PyBindModule::remapNames(orCrit);
  registerSubclass<WayNodeCriterion>(m, wrapme);


}

REGISTER_PYHOOT_SUBMODULE(init_ElementCriterion)

}
