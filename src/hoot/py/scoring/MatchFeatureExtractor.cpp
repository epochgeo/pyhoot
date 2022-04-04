/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/scoring/MatchFeatureExtractor.h>
#include <hoot/core/conflate/matching/MatchCreator.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace hoot;

static void init_MatchFeatureExtractor(py::module_& m)
{
  auto wrapme =
    py::class_<MatchFeatureExtractor, std::shared_ptr<MatchFeatureExtractor> >
      (m, "MatchFeatureExtractor")
    .def(py::init([](bool evenClasses) {
      return new MatchFeatureExtractor(evenClasses);
    }))
    .def("addMatchCreator", &MatchFeatureExtractor::addMatchCreator, R"TOK(
Adds a match creator to the list of matches that will be evaluated. There must be at least one.
The match creator's matches must implement MatchDetails.
)TOK")
    .def("getResults", &MatchFeatureExtractor::getResults, R"TOK(
Returns the results as an ARFF file: http://www.cs.waikato.ac.nz/ml/weka/arff.html
)TOK")
    .def("getSamples", &MatchFeatureExtractor::getSamples)
    .def("getSampleList", [](MatchFeatureExtractor& self) {
      return (std::vector<std::map<QString, double> >)self.getSamples();
    })
    .def("processMap", &MatchFeatureExtractor::processMap, R"TOK(
Evaluates all the features in the given map.
)TOK")

  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_MatchFeatureExtractor)

}
