/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2022 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/conflate/review/ReviewMarker.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

void init_ReviewMarker(py::module_& m)
{
  auto wrapme = py::class_<ReviewMarker, std::shared_ptr<ReviewMarker> >(m, "ReviewMarker")
    .def(py::init<>())
    .def("mark", [](ReviewMarker& self,
          const OsmMapPtr& map,
          const ConstElementPtr& e1,
          const ConstElementPtr& e2,
          const QString& note,
          const QString& reviewType,
          double score = -1,
          const std::vector<QString>& choices = std::vector<QString>()){
        self.mark(map, e1, e2, note, reviewType, score, choices);
      },
      py::arg("map"),
      py::arg("e1"),
      py::arg("e2"),
      py::arg("note"),
      py::arg("reviewType"),
      py::arg("score") = -1,
      py::arg("choices") = std::vector<QString>(),
      R"TOK(
Marks e1 and e2 as needing review and sets them to reference each other. If the score is
negative then the score is omitted.

:param note: A human readable note describing the review.
:param reviewType: A human readable review type. Typically this is a one word description of
 the feature being reviewed. E.g. "Highway" or "Building".
)TOK")
//    .def("mark", &ReviewMarker::mark, R"TOK(
//Marks a set of elements as needing review and sets them to reference each other. If the score
//is negative then the score is omitted.

//:param note: A human readable note describing the review.
//:param reviewType: A human readable review type. Typically this is a one word description of
// the feature being reviewed. E.g. "Highway" or "Building".
//)TOK")
//    .def("mark", &ReviewMarker::mark, R"TOK(
//Marks a single element as needing review.
//)TOK")
    .def("mark", [](ReviewMarker& self,
          const OsmMapPtr& map,
          const std::vector<ElementId>& ids,
          const QString& note,
          const QString& reviewType,
          double score = -1,
          const std::vector<QString>& choices = std::vector<QString>()){
        self.mark(map, ids, note, reviewType, score, choices);
        //PyErr_Print();
        // TODO: remove me
        PyErr_Clear();
      },
      py::arg("map"),
      py::arg("ids"),
      py::arg("note"),
      py::arg("reviewType"),
      py::arg("score") = -1,
      py::arg("choices") = std::vector<QString>(),
      R"TOK(
Marks a vector of elements as needing review and sets them to reference each other. If the score
is negative then the score is omitted.

:param note: A human readable note describing the review.
:param reviewType: A human readable review type. Typically this is a one word description of
 the feature being reviewed. E.g. "Highway" or "Building".
)TOK")
    .def_static("getBadGeometryType", &ReviewMarker::getBadGeometryType)
    .def_static("getReviewElements", &ReviewMarker::getReviewElements)
//    .def_static("getReviewUids", &ReviewMarker::getReviewUids)
//    .def_static("getReviewUids", &ReviewMarker::getReviewUids)
//    .def_static("getReviewUids", &ReviewMarker::getReviewUids)
    .def_static("getReviewType", &ReviewMarker::getReviewType)
//    .def_static("isNeedsReview", &ReviewMarker::isNeedsReview, R"TOK(
//Returns true if the element is in at least one review.
//)TOK")
//    .def_static("isNeedsReview", &ReviewMarker::isNeedsReview, R"TOK(
//Determines whether a pair of elements should be returned for review

//:param e1: the first element in the element pair being examined
//:param e2: the second element in the element pair being examined
//:returns: true if the pair should be reviewed against each other; false otherwise
//)TOK")
    .def_static("isReview", &ReviewMarker::isReview, R"TOK(
Returns true if this element is a review record (not an element that needs to be reviewed, but
the relation that describes the review).

isReviewUid is preferred over this method. If we change the review mechanism in the future
this method may be broken. (unlikely)
)TOK")
    .def_static("isReviewUid", &ReviewMarker::isReviewUid, R"TOK(
Returns true if the specified UID is a review tag.
)TOK")
    .def_static("removeElement", &ReviewMarker::removeElement, R"TOK(
Removes a single element.
)TOK")
  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_ReviewMarker)

}
