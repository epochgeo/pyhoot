/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <hoot/core/algorithms/extractors/EuclideanDistanceExtractor.h>
#include <hoot/core/algorithms/extractors/NameExtractor.h>
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/geometry/ElementToGeometryConverter.h>

#include <hoot/py/bindings/HootInterfaces.h>

// pybind11
#include <pybind11/numpy.h>

#include "CircularErrorExtractor.h"
#include "StatusEqualsExtractor.h"
#include "TagMatchExtractor.h"

namespace py = pybind11;
using namespace std;

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
    .def("extract", [](const FeatureExtractor& self,
        const OsmMap& map, const vector<ConstElementPtr>& target,
          const vector<ConstElementPtr>& candidate,
          vector<bool> ignored) {
        assert(target.size() == candidate.size());
        // return a numpy array
        auto result = py::array_t<double>(target.size());
        double* resultPtr = static_cast<double*>(result.request().ptr);
        for (size_t i = 0; i < target.size(); i++)
        {
          double value;
          if (i < ignored.size() && ignored[i])
          {
            value = self.nullValue();
          }
          else
          {
            value = self.extract(map, target[i], candidate[i]);
          }
          resultPtr[i] = value;
        }
        return result;
    }, R"TOK(
This override to the distance function is pyhoot specific and allows you to calculate distance
on an array of values in one pass.
)TOK",
      py::arg("map"),
      py::arg("target"),
      py::arg("candidate"),
      py::arg("ignored") = vector<bool>())
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
  auto circularError = registerSubclass<CircularErrorExtractor>(m, wrapme);
  circularError.def(py::init([](int input) { return make_shared<CircularErrorExtractor>(input); }));

  auto status = registerSubclass<StatusEqualsExtractor>(m, wrapme);
  status.def(py::init([](Status::TypeEnum status) {
    return make_shared<StatusEqualsExtractor>(status);
  }));

  auto tagMatch = registerSubclass<TagMatchExtractor>(m, wrapme);
  tagMatch.def(py::init([](QString key) {
    return make_shared<TagMatchExtractor>(key);
  }));

}

REGISTER_PYHOOT_SUBMODULE(init_FeatureExtractor)

}
