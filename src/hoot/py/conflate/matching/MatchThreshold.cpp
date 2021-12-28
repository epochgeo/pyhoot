/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/matching/MatchThreshold.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace std;

static void init_MatchThreshold(py::module_& m)
{
  auto wrapme = py::class_< MatchThreshold, shared_ptr<MatchThreshold> >(m, "MatchThreshold")
    .def(py::init<>())
    .def(py::init([](double match, double miss, double review) {
      return make_shared<MatchThreshold>(match, miss, review);
    }), R"TOK(
Constructor

:param matchThreshold: the score threshold at which a match object is considered a match
:param missThreshold: the score threshold at which a match object is considered a miss
:param reviewThreshold: the score threshold at which a match object is considered a review
:param validateRange: if true, the range (0.0, 1.0] will be honored. For conflate usage we
generally want to honor that range for thresholds. In some instances, though, we may not want
to.
)TOK")
    .def("__str__", &MatchThreshold::toString)

    .def_property_readonly("match_threshold", &MatchThreshold::getMatchThreshold)
    .def_property_readonly("miss_threshold", &MatchThreshold::getMissThreshold)
    .def_property_readonly("review_threshold", &MatchThreshold::getReviewThreshold)

  // MatchType getType(const Match& m) const { return getType(m.getClassification()); }
  // MatchType getType(const MatchClassification& mc) const;
//     .def("getTypeDetail", &MatchThreshold::getTypeDetail,
// R"TOK(
// Returns human readable information about the match type

// :param mc: match classification
// :returns: match type information
// )TOK")
    .def("toString", &MatchThreshold::toString)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_MatchThreshold)

}
