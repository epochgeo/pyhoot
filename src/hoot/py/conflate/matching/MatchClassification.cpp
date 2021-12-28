/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/conflate/matching/MatchClassification.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace std;

static void init_MatchClassification(py::module_& m)
{
  auto wrapme = py::class_< MatchClassification, shared_ptr<MatchClassification> >
    (m,"MatchClassification")
    .def(py::init<>())
    .def(py::init([](double match, double miss, double review) {
      return make_shared<MatchClassification>(match, miss, review);
    }), R"TOK(
The match classification object represents the classification of a match. A match may be in
one of three states:

 - match - we're confident the two elements represent the same feature
 - miss - we're confident the two elements do not represent the same feature
 - review - we're confident the data is ambiguous or wrong and it requires human review

Of course, there are different levels to each of those states. This class represents those
varying levels of confidence.
)TOK")
    .def("__str__", &MatchClassification::toString)

    .def_property("match",
      &MatchClassification::getMatchP,
      &MatchClassification::setMatchP)
    .def_property("miss",
      &MatchClassification::getMissP,
      &MatchClassification::setMissP)
    .def_property("review",
      &MatchClassification::getReviewP,
      &MatchClassification::setReviewP)

    .def("toString", &MatchClassification::toString)
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_MatchClassification)

}
