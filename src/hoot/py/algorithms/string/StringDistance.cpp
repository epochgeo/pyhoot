/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <hoot/core/algorithms/string/ExactStringDistance.h>
#include <hoot/core/algorithms/string/KskipBigramDistance.h>
#include <hoot/core/algorithms/string/LevenshteinDistance.h>
#include <hoot/core/algorithms/string/MaxWordSetDistance.h>
#include <hoot/core/algorithms/string/MeanWordSetDistance.h>
#include <hoot/core/algorithms/string/MinSumWordSetDistance.h>
#include <hoot/core/algorithms/string/MostEnglishName.h>
#include <hoot/core/algorithms/string/Soundex.h>
#include <hoot/core/algorithms/string/WeightedWordDistance.h>
#include <hoot/core/language/ToEnglishTranslateStringDistance.h>

#include <hoot/py/bindings/HootInterfaces.h>

namespace py = pybind11;

namespace hoot
{

void init_StringDistance(py::module_& m)
{
  auto wrapme = py::class_<StringDistance, std::shared_ptr<StringDistance> >
    (m, "StringDistance")
    .def("compare", &StringDistance::compare, R"TOK(
compare returns a value from 1 (very similar) to 0 (very dissimilar) describing the
distance between two strings.
)TOK")
  ;

  PyBindModule::remapNames(wrapme);

  registerSubclass<ExactStringDistance>(m, wrapme);
  registerSubclass<KskipBigramDistance>(m, wrapme);
  registerSubclass<LevenshteinDistance>(m, wrapme);
  registerSubclass<MaxWordSetDistance>(m, wrapme);
  registerSubclass<MeanWordSetDistance>(m, wrapme);
  registerSubclass<MinSumWordSetDistance>(m, wrapme);
  registerSubclass<Soundex>(m, wrapme);
  registerSubclass<ToEnglishTranslateStringDistance>(m, wrapme);
  registerSubclass<WeightedWordDistance>(m, wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_StringDistance)

}
