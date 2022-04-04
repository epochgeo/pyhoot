/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Qt
#include <QSet>

// hoot
#include <hoot/core/schema/OsmSchema.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_OsmSchema(py::module_& m)
{
    auto osmSchema = py::class_<hoot::OsmSchema, std::unique_ptr<OsmSchema, py::nodelete> >
        (m, "OsmSchema")
        .def(py::init([]() { return &OsmSchema::getInstance(); }))
        .def_static("getInstance",
          []() { return &OsmSchema::getInstance(); },
          R"TOK(
get_instance() is provided for consistency w/ hoot but just calling OsmSchema() gives the same
result and is more concise.
)TOK")

  //static OsmSchema& getInstance()

        .def("loadDefault", &OsmSchema::loadDefault,
R"TOK(
Loads the default configuration. This should only be used by unit tests."
)TOK")

        .def("createTestingGraph", &OsmSchema::createTestingGraph,
R"TOK(
ONLY FOR UNIT TESTING. Be a good neighbor and call loadDefault() when you're done."
)TOK")
        .def("addAssociatedWith", &OsmSchema::addAssociatedWith)
        .def("addIsA", &OsmSchema::addIsA)
        .def("addSimilarTo", &OsmSchema::addSimilarTo)
        .def("update", &OsmSchema::update)
        .def("updateOrCreateVertex", &OsmSchema::updateOrCreateVertex)

        // .def("average", &OsmSchema::average)
        // .def("average", &OsmSchema::average)


        .def("getFirstCommonAncestor", &OsmSchema::getFirstCommonAncestor,
R"TOK(
Searches for the first common ancestor between two key value pairs. If there is no common
ancestor then an empty TagVertex is returned."
)TOK")
        .def("isAncestor", &OsmSchema::isAncestor)
        // .def("getCategories", &OsmSchema::getCategories)
        // .def("getCategories", &OsmSchema::getCategories)
        // .def("getCategories", &OsmSchema::getCategories)


        .def("getAssociatedTags", &OsmSchema::getAssociatedTags,
R"TOK(
Retrieves a set of tags that are associated with the input tags, as defined by the hoot schema

:param tags: tags to search associations for
:returns: a set of tags"
)TOK")

        .def("getChildTags", &OsmSchema::getChildTags,
R"TOK(
Retrieves all child tags for the given input tags

:param tags: tags for which to retrieve child tags
:returns: a set of tags"
)TOK")

        .def("getSimilarTags", &OsmSchema::getSimilarTags,
R"TOK(
Retrieves tags similar to the input tag

:param name: a kvp
:param minimumScore: tag similarity threshold
:returns: a set of tags"
)TOK")


        .def("getAllTagKeys", &OsmSchema::getAllTagKeys,
R"TOK(
Retrieves all possible tag keys from the schema

:returns: a collection of key strings
)TOK")
        .def("hasTagKey", &OsmSchema::hasTagKey)

        .def("tags", &OsmSchema::getGenericKvps,
R"TOK(
Returns a collection of tag key/value pairs that represent generic feature types

:returns: a collection of tag key/value pairs
)TOK")

        .def("getAliasTags", &OsmSchema::getAliasTags,
R"TOK(
Retrieves tags that are aliases of the input tags

:param tags: tags to search aliases for
:returns: a set of tags"
)TOK")

        .def("getParentKvp", &OsmSchema::getParentKvp,
R"TOK(
Determine the ancestor between two tags

:param kvp1: first tag to examine
:param kvp2: second tag to examine
:returns: tag that is the ancestor of the other or the first tag if neither is an ancestor of
each other"
)TOK")

        .def("getAllTags", &OsmSchema::getAllTags)
        .def("getSimilarTagsAsVertices", &OsmSchema::getSimilarTagsAsVertices,
R"TOK(
Returns all tags that have a similar score >= minimumScore.

minimumScore must be > 0.
)TOK")
  // std::vector<SchemaVertex> getTagByCategory(const OsmSchemaCategory& c) const;
  // std::vector<SchemaVertex> getChildTagsAsVertices(const QString& name) const;
  // std::vector<SchemaVertex> getAssociatedTagsAsVertices(const QString& name) const;

        .def("getTagVertex", &OsmSchema::getTagVertex,
R"TOK(
Returns the tag vertex for a given kvp. If the vertex is compound then an empty vertex will
be returned.
)TOK")


        .def("getSchemaVertices", &OsmSchema::getSchemaVertices,
R"TOK(
Returns all schema vertices that are represented in the set of tags. This will return both
compound vertices and tag vertices.
)TOK")


//         .def("hasCategory", &OsmSchema::hasCategory,
// R"TOK(
// Returns true if at least one tag in the set of specified tags is part of the specified
// category."
// )TOK")

//         .def("hasCategory", &OsmSchema::hasCategory,
// R"TOK(
// Returns true if the specified kvp is part of the specified category."
// )TOK")

//         .def("hasCategory", &OsmSchema::hasCategory,
// R"TOK(
// Returns true if at least one tag in the set of specified tags is part of the specified
// category."
// )TOK")

//         .def("hasCategory", &OsmSchema::hasCategory,
// R"TOK(
// Returns true if the specified kvp is part of the specified category."
// )TOK")

        .def("hasAnyCategory", &OsmSchema::hasAnyCategory,
R"TOK(
Determines if the key is part of any category in the schema

:param key: tag key
:param val: tag value
:returns: true if the tag is part of at least one schema category; false otherwise
)TOK")
        // .def("allowsFor", &OsmSchema::allowsFor)
        // .def("allowsFor", &OsmSchema::allowsFor)

        .def("isList", &OsmSchema::isList,
R"TOK(
Returns true if this is a list of values. Right now this just looks for a semicolon in value,
but in the future the list of valid list keys may be stored in the schema file."
)TOK")

        .def("isMetaData", &OsmSchema::isMetaData,
R"TOK(
Returns true if the kvp contains metadata about the feature as opposed to real information
about the features.

Tags such as \"hoot:status\", \"source", \"uuid\""
)TOK")

// No longer valid?
//         .def("isReversed", &OsmSchema::isReversed,
// R"TOK(
// Returns true if this is a reversed unidirectional way. (E.g. oneway=reverse)"
// )TOK")

        .def("isTextTag", &OsmSchema::isTextTag,
R"TOK(
Return true if this tag can contain free-form text."
)TOK")

        .def("isNumericTag", &OsmSchema::isNumericTag,
R"TOK(
Return true if this tag can contain numeric text."
)TOK")
        .def("getIsACost", &OsmSchema::getIsACost)
//         .def("score", &OsmSchema::score)
        .def("score", [](const OsmSchema& self, const SchemaVertex& v1, const SchemaVertex& v2) {
           return self.score(v1, v2);
        })

        .def("score", [](const OsmSchema& self, const QString& kvp, const Tags& tags) {
           return self.score(kvp, tags);
        },
R"TOK(
Scores a particular kvp against an element's tags

:param kvp: the key/value pair to compare against
:param tags: the tags to compare against
:returns: the highest similarity score found in tags when compared to kvp"
)TOK")

        .def("scoreTypes", &OsmSchema::scoreTypes,
R"TOK(
Scores the type similarity between two sets of tags

:param tags1: the first set of tags to score
:param tags2: the second set of tags to score
:param ignoreGenericTypes: if true, generic types such as 'poi=yes' are ignored during
comparison
:returns: a similarity score from 0.0 to 1.0"
)TOK")

        .def("scoreOneWay", &OsmSchema::scoreOneWay,
R"TOK(
@brief scoreOneWay Returns a oneway score. E.g. highway=primary is similar to highway=road,
 but a highway=road isn't necessarily similar to a highway=primary (so it gets a low score)."
)TOK")


        .def("getFirstType", &OsmSchema::getFirstType,
R"TOK(
Returns the first type key/value pair found in a set of tags

:param tags: the tags to search
:param allowGeneric: if true, kvps associated with generic types are returned
:returns: a single key/value pair string"
)TOK")


        .def("explicitTypeMismatch", &OsmSchema::explicitTypeMismatch,
R"TOK(
Determines if two sets of tags have an explicit type mismatch. Empty tags and generic types
are ignored during the comparison

:param tags1: the first set of tags to compare
:param tags2: the second set of tags to compare
:param minTypeScore: the minimum similarity score at or above which the two sets of tags must
score in to be considered a match
:returns: true if the tags explicitly mismatch; false otherwise"
)TOK")

        .def("typeMismatch", &OsmSchema::typeMismatch,
R"TOK(
Determines if two sets of tags have an explicit type mismatch. Empty tags and generic types
are not ignored during the comparison

:param tags1: the first set of tags to compare
:param tags2: the second set of tags to compare
:param minTypeScore: the minimum similarity score at or above which the two sets of tags must
score in to be considered a match
:returns: true if the tags mismatch; false otherwise"
)TOK")

        .def("isGenericKvp", &OsmSchema::isGenericKvp,
R"TOK(
Determines if a key/value pair represents a generic feature type

:param kvp: the key/value pair to examine
:returns: true if the input key/value pair represents a generic type; false otherwise"
)TOK")

        .def("isGeneric", &OsmSchema::isGeneric,
R"TOK(
Determines whether a set of tags represents a generic feature type

:param tags: the tags to examine
:returns: true if the tags contain only a generic feature type; false otherwise"
)TOK")

        .def("hasType", &OsmSchema::hasType,
R"TOK(
Determines if a set of tags has a feature type

:param tags: the tags to examine
:returns: true if the tags have at least one type tag"
)TOK")

        .def("hasMoreThanOneType", &OsmSchema::hasMoreThanOneType,
R"TOK(
Determines if a set of tags have more than one feature type

:param tags: the tags to examine
:returns: true if the tags have at least two type tags"
)TOK")

        .def("mostSpecificType", &OsmSchema::mostSpecificType,
R"TOK(
Returns the most specific type in a set of tags according to the schema

:param tags: the tags to search
:returns: a single key/value pair string"
)TOK")

        .def("isTypeKey", &OsmSchema::isTypeKey,
R"TOK(
Determines if a tag key corresponds to a type in the schema

:param key: tag key to examine
:returns: true if the key corresponds to a type; false otherwise"
)TOK")
        .def("toGraphvizString", &OsmSchema::toGraphvizString)
        .def_static ("toKvp", &OsmSchema::toKvp)


        .def("setIsACost", &OsmSchema::setIsACost,
R"TOK(
Sets the cost when traversing up the tree to a parent node. This is useful for strict score
checking rather than equivalent tags."
)TOK")
        ;

     PyBindModule::remapNames(osmSchema);
}

REGISTER_PYHOOT_SUBMODULE(init_OsmSchema)

}
