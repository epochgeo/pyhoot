/**
 * The original code by Maxar/NGA is licensed under GPLv3.
 * 
 * All EpochGeo modifications to the code are licensed under the MIT or at your discretion the
 * GPLv3 license.
 *
 * --------------------------------------------------------------------
 *
 * @copyright Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021 Maxar (http://www.maxar.com/)
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#include "PythonCreatorDescription.h"

// hoot
#include <hoot/core/conflate/matching/MatchClassification.h>
#include <hoot/core/conflate/matching/MatchThreshold.h>
#include <hoot/core/info/CreatorDescription.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

// pybind11
#include <pybind11/functional.h>

namespace py = pybind11;
using namespace std;

namespace hoot
{

void init_PythonCreatorDescription(py::module_& m)
{
    auto wrapme = py::class_<PythonCreatorDescription, shared_ptr<PythonCreatorDescription> >(
        m, "PythonCreatorDescription")
      .def(py::init<>())
      .def_property("criteria", &PythonCreatorDescription::getCriteria,
        &PythonCreatorDescription::setCriteria,
        "criteria contains a list of criterion names to apply before matching. E.g. PoiCriterion")
      .def_property("is_match_candidate",
        &PythonCreatorDescription::getIsMatchCandidate,
        &PythonCreatorDescription::setIsMatchCandidate,
        R"TOK(is_match_candidate is called to evaluate two elements for match candidacy.

:returns: True if the two elements might match. A more restrictive function will run faster later
    in the process, sometimes dramatically faster.
)TOK")
      .def_property("is_whole_group",
        &PythonCreatorDescription::getIsWholeGroup,
        &PythonCreatorDescription::setIsWholeGroup,
        R"TOK(is_whole_group is a function that is called to determine if the
matches generated by this matcher should be treated as a group, or as
a graph that should be deconflicted.

An example of whole group would be 2 buildings, and 2 points that all represent
a single POI that you want to conflate into a single polygon.

:returns: True if the matches should be treated as a whole group.
)TOK")
      .def_property("match_score",
        &PythonCreatorDescription::getMatchScore,
        &PythonCreatorDescription::setMatchScore,
R"TOK(match_score determines scores a pair of elements with a match/miss/review.
score. The sum of all the scores _should_ add to one.

Example return value:

  return (hoot.MatchClassification(1, 0, 0), "obvious to robots")

:returns: A tuple with (MatchClassification, string) where the MatchClassification object has the
match, miss & review scores populated and the score contains a human readable explanation of why
the match classification was chosen.
)TOK")
      .def_property("match_threshold", &PythonCreatorDescription::getMatchThreshold,
        &PythonCreatorDescription::setMatchThreshold,
        "match_threshold determines what value is a match/miss/review.")
      .def_property("merge_pair",
        &PythonCreatorDescription::getMergePair,
        &PythonCreatorDescription::setMergePair,
R"TOK(merge_pair merges a pair of matched elements into one element.

:returns: The merged element.
)TOK")
      .def_property("merge_set",
        &PythonCreatorDescription::getMergeSet,
        &PythonCreatorDescription::setMergeSet,
R"TOK(merge_set merges a set of matched elements into one element. Any elements that are replaced
must be returned as an array of element ID tuples.


:param map: The OsmMap that contains the elements to merge.
:param pairs: A set of pairs of element IDs. These are the interrelated matched pairs.
:returns: The replaced pairs. E.g. [(ElementId('way:1'), ElementId('way:100'))]
)TOK")
      .def_property("search_radius",
        &PythonCreatorDescription::getSearchRadius,
        &PythonCreatorDescription::setSearchRadius,
R"TOK(search_radius is the fixed search radius for all elements, use this or 
search_radius_function but not both.)TOK")
      .def_property("search_radius_function",
        &PythonCreatorDescription::getSearchRadiusFunction,
        &PythonCreatorDescription::setSearchRadiusFunction,
R"TOK(search_radius_function is a function that returns a customized search radius per element
in lieu of a fixed search_radius. This is useful when different elements have different radii,
for example: towns and cities.)TOK")
      .def_property_readonly("description",
        &PythonCreatorDescription::getDescription,
        "description is used to set matcher/merger routine metadata.");
    ;
    hoot::PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_PythonCreatorDescription)

PythonCreatorDescription::PythonCreatorDescription()
{
  LOG_TRACE("PythonCreatorDescription");
  _desc = make_shared<CreatorDescription>();
  _matchThreshold = make_shared<MatchThreshold>();
}

PythonCreatorDescription::~PythonCreatorDescription()
{
}

void PythonCreatorDescription::clear()
{
  LOG_TRACE("clear");
  _desc = nullptr;
  _initFunc = nullptr;
  _isMatchCandidateFunc = nullptr;
  _matchScoreFunc = nullptr;
  _mergePairFunc = nullptr;
}

CreatorDescriptionPtr PythonCreatorDescription::getDescription() { return _desc; }

void PythonCreatorDescription::setIsMatchCandidate(IsMatchCandidateFunction func)
{
    _isMatchCandidateFunc = func;
}

void PythonCreatorDescription::setSearchRadius(Meters radius)
{
  LOG_TRACE("setSearchRadius");
  _searchRadius = radius;
}

void PythonCreatorDescription::setSearchRadiusFunction(SearchRadiusFunction func)
{
  LOG_TRACE("setSearchRadius");
  _searchRadiusFunc = func;
}

}