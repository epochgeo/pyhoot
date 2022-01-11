/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <hoot/core/algorithms/extractors/EuclideanDistanceExtractor.h>
#include <hoot/core/algorithms/extractors/NameExtractor.h>
#include <hoot/core/elements/OsmMap.h>

#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

namespace hoot
{

void init_FeatureExtractor(py::module_& m)
{
  auto wrapme = py::class_<FeatureExtractor, std::shared_ptr<FeatureExtractor> >
    (m, "FeatureExtractor")
    .def("__str__", &FeatureExtractor::toString)
    .def("extract", &FeatureExtractor::extract, R"TOK(
extract extracts a feature from a given pair of elements.

The feature may be something like the distance between colors, the overlap of two polygons,
etc.
)TOK")
    .def("toString", &FeatureExtractor::toString)
    .def("getFactorType", &FeatureExtractor::getFactorType, R"TOK(
getFactorType returns the factor type for this feature/factor (Nominal or Numeric).
)TOK")
    .def("getNullTreatment", &FeatureExtractor::getNullTreatment, R"TOK(
getNullTreatment returns the null treatment for this feature/factor (NullAsValue or
NullAsMissingValue).
)TOK")
    .def_static ("isNull", &FeatureExtractor::isNull)
  ;

  PyBindModule::remapNames(wrapme);

  registerSubclass<EuclideanDistanceExtractor>(m, wrapme);
  registerSubclass<NameExtractor>(m, wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_FeatureExtractor)

}
