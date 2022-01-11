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
#include <hoot/core/criterion/PointCriterion.h>
#include <hoot/core/criterion/PolygonCriterion.h>

#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

namespace hoot
{

void init_ElementCriterion(py::module_& m)
{
  auto wrapme = py::class_<ElementCriterion, std::shared_ptr<ElementCriterion> >
    (m, "ElementCriterion")
    .def("__str__", &ElementCriterion::toString)
    .def("isSatisfied", &ElementCriterion::isSatisfied)
    .def("clone", &ElementCriterion::clone)
    .def("toString", &ElementCriterion::toString)
  ;

  PyBindModule::remapNames(wrapme);

  registerSubclass<AreaCriterion>(m, wrapme);
  registerSubclass<HasNameCriterion>(m, wrapme);
  registerSubclass<LinearCriterion>(m, wrapme);
  registerSubclass<PointCriterion>(m, wrapme);
  registerSubclass<PolygonCriterion>(m, wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_ElementCriterion)

}
