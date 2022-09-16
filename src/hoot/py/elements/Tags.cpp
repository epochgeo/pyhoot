/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>

#include <hoot/core/elements/Element.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_Tags(py::module_& m)
{
    // This is a lazy wrapping of Tags. All the functions have been wrapped to some degree but
    // the more difficult functions have been commented out.
    //
    // No new comments have been added but existing hoot comments have been converted to python
    // style docstrings.
    auto tags = py::class_<hoot::Tags>(m, "Tags"/*,
R"TOK(
Contains a set of key/value pairs. Consistent with the OSM way of doing things [1] if there are
multiple values with a single key, the values are semi-colon delimited. There is currently
no way to differentiate between a value that happens to contain a semi-colon and a list, although
using ;; has been proposed it isn't in use. Given that I haven't found any instances where this
is an issue, I'm not going to worry about it at this time.

1. http://wiki.openstreetmap.org/wiki/Semi-colon_value_separator

Its interesting to note that if you add a copy constructor to this class, you'll blow up a lot
of the code that isn't intending to copy tags but then does after the change (understandable).
If you try to add a copy constructor delete to disable it (or just make it private), you'll blow
up ElementData's inline constructor, which apparently is using the copy constructor to set its
tags. It seems like a copy constructor could be useful in certain situations...so may be worth
looking into at some point.
)TOK"*/)
        .def(py::init<>())
        .def(py::init([](QString key, QString value) { return new Tags(key, value); }))

        .def("__repr__", &Tags::toString)
        .def("__str__", &Tags::toString)
        .def("__getitem__", &Tags::get)
        .def("__setitem__", [](Tags& self, QString k, QString v) { self.set(k, v); })
        .def("to_dict", [](const Tags& tags) {
          std::map<QString, QString> result;
          result.insert(tags.keyValueBegin(), tags.keyValueEnd());
          return result;
        })
        .def("clone", [](const Tags& tags) {
          Tags result = tags;
          return result;
        })

        .def_static("className", &Tags::className)
        .def_static("uuidKey", &Tags::uuidKey)

        // bool operator==(const Tags& other) const;
        // inline bool operator!=(const Tags& other) const { return !(*this == other); }

        .def("addNote", &Tags::addNote)
        .def("add", &Tags::add,
R"TOK(
Adds all the tags in t into this set of tags. Tags in t overwrite tags in this.
)TOK")

        .def("appendValue", 
            static_cast<void (Tags::*)(const QString&, const QString&)>(&Tags::appendValue),
R"TOK(
Appends a value to a key. If the key already has a value then the values are semi-colon
delimited. If the key has no value then it is equivalent to simply setting the tag.
)TOK")
        // .def("appendValue", &Tags::appendValue)
        // .def("appendValue", &Tags::appendValue)
        // .def("appendValue", &Tags::appendValue)


        .def("appendValueIfUnique", 
            static_cast<void (Tags::*)(const QString&, const QString&)>(&Tags::appendValueIfUnique),
R"TOK(
Appends a value to a key. If the key already has a value then the values are semi-colon
delimited. If the key has no value then it is equivalent to simply setting the tag.

The value is only appended if it doesn't already exist in the list.
)TOK")
        // .def("appendValueIfUnique", &Tags::appendValueIfUnique)


        .def("hasInformationTag", &Tags::hasInformationTag,
R"TOK(
Return if there is at least one non-metadata tag. @sa getInformationalCount()
)TOK")
        .def("get", &Tags::get)


        .def("getCreateUuid", &Tags::getCreateUuid,
R"TOK(
Gets the element's UUID(s). If the UUID doesn't exist then it creates a new UUID.

Given that elements can be conflated and all the old UUIDs are maintained, you may get a list
of multiple UUIDs. All of these UUIDs reference the same element.
)TOK")


        .def("getDouble", [](const Tags& self, QString k) { return self.getDouble(k); },
R"TOK(
Returns a double version of the value associated with k. If it cannot be parsed into a double
then an exception is thrown.
)TOK")
        // .def("getDouble", &Tags::getDouble)


        .def("getList", &Tags::getList,
R"TOK(
Returns the list of values associated with the key k. If k starts with regex? then all values
associated with the regular expression after regex? are returned. E.g. regex?a.* will return
all values that start with a. The order of the results is arbitrary.
)TOK")


        .def("getMatchingKeys", &Tags::getMatchingKeys,
R"TOK(
Given a list of keys (that may include regex values), find all the keys in this Tags set that
match one or more entries in the list and return it. Each key will only be returned at most
once.
)TOK")


        .def_static("getNameKeys", []() { return Tags::getNameKeys(); },
R"TOK(
Return all the keys that are used in names.
)TOK")

        .def_static("getNameKeys", [](const Tags& tags) { return Tags::getNameKeys(tags); },
R"TOK(
Get name keys for a set of tags

:param tags: tags to parse name keys from
:returns: a list of name keys
)TOK")

        .def("getNames", &Tags::getNames,
R"TOK(
Return all the names for the current feature.

:param include_alt_name: if true, returns names with the alt_name tag key
)TOK",
          py::arg("include_alt_name") = true)

        .def("getName", &Tags::getName,
R"TOK(
Returns a name given tags

:returns: the first name found, if one is present
)TOK")

        .def("getPseudoNames", &Tags::getPseudoNames,
R"TOK(
Return all the names associated with the feature. These are more loosely defined and may
include things like operator name and brand name. See conf/NameSchema.json for a definition.
)TOK")

        .def("getVelocity", &Tags::getVelocity,
R"TOK(
Returns the speed in standard units (m/s).
)TOK")

        .def("getLength", &Tags::getLength,
R"TOK(
Returns the length in standard units (m).
)TOK")

        .def("getInformationCount", &Tags::getInformationCount,
R"TOK(
Return the number of tags that contain actual information, not meta-data or debug tags.
Meta-data tags include things like source and license. Debug is anything that starts with
hoot:. An example of an informational tag is name or highway.
)TOK")
        .def("getNonDebugCount", &Tags::getNonDebugCount)

        .def("isFalse", &Tags::isFalse,
R"TOK(
Checks for common false values such as 'no', 'false', '0', 'off'.

Note: It is not guaranteed that isFalse(tag) != isTrue(tag), but you are guaranteed that if
one of them is true the other will be false. E.g. value=apple will return false for both
methods.
)TOK")


        .def("isTrue", &Tags::isTrue,
R"TOK(
Checks for common true values such as 'yes', 'true', '1', 'on'.

Note: It is not guaranteed that isFalse(tag) != isTrue(tag), but you are guaranteed that if
one of them is true the other will be false. E.g. value=apple will return false for both
methods.
)TOK")


        .def("dataOnlyEqual", &Tags::dataOnlyEqual,
R"TOK(
Similar to operator== but 'hoot:*' tags are ignored
)TOK")


        .def("hasSameNonMetadataTags", &Tags::hasSameNonMetadataTags,
R"TOK(
Determines if two sets of tags have the same information values

This may have overlap with dataOnlyEqual, however the two have differences...worth looking
into at some point.

:param other: tags to compare with
:returns: true if both sets of tags have the same information values; false otherwise
)TOK")


        .def("getDataOnlyValues", &Tags::getDataOnlyValues,
R"TOK(
Get a list of all non-'hoot:*' tags
)TOK")
        .def("readValues", &Tags::readValues)
        .def("readMeters", &Tags::readMeters)


        .def("removeMetadata", &Tags::removeMetadata,
R"TOK(
Removes all metadata tags (hoot:* and those identified in the schema)

:returns: the number of tags removed
)TOK")

        .def("remove", &Tags::remove)

        .def("removeKeys", 
            [](Tags& self, const QStringList& keys) { self.removeKeys(keys); },
R"TOK(
Removes all tags with keys exactly matching those in the input list

:param keys: the list of keys to remove
:returns: the number of tags removed
)TOK")

//         .def("removeKey", &Tags::removeKey,
// R"TOK(
// Removes any tag who's key matches the input regular expression

// :param regex: regular expression to match
// :returns: the number of tags removed
// )TOK")

//         .def("removeKeys", &Tags::removeKeys,
// R"TOK(
// Removes all tags who's keys match the input regular expressions

// :param regexes: regular expressions to match
// :returns: the number of tags removed
// )TOK")


        .def("removeByTagKeyStartsWith", &Tags::removeByTagKeyStartsWith,
R"TOK(
Removes all tags with keys that start with the input substring

:param tagKeySubstring: a substring to match
:returns: the number of tags removed
)TOK")


        .def("setArea", &Tags::setArea,
R"TOK(
Sets the area tag to either true (is an area element), or false (is not an area element)
)TOK")


        .def("set", [](Tags& self, QString key, QString value) { self.set(key, value); },
R"TOK(
If a kvp is in other, then set it in this. If this already has that key then the value will
be overwritten.
)TOK")
//   void set(const QString& key, bool v)
//   void set(const QString& key, double v) { set(key, QString::number(v)); }
//   void set(const QString& key, int v) { set(key, QString::number(v)); }
//   void set(const QString& key, int64_t v) { set(key, QString::number(v)); }
// R"
// If a kvp is in other, then set it in this. If this already has that key then the value will
// be overwritten.
// "
//   void set(const Tags& other)
        .def("setList", &Tags::setList)


        .def("split", &Tags::split,
R"TOK(
Splits the specified value up into individual values. For now it just splits on ";", but it
may get more robust later.
)TOK")



        .def_static("isValidKvp", &Tags::isValidKvp,
R"TOK(
Determines if a string is a valid tag key/value pair

:param str: the string to examine
:returns: true if the input string is a valid kvp; false otherwise
)TOK")

        .def("kvpToKey", &Tags::kvpToKey,
R"TOK(
Extracts a tag key from a tag key/value pair

:param kvp: string to extract from
:returns: a tag key string
)TOK")

        .def("kvpToVal", &Tags::kvpToVal, 
R"TOK(
Extracts a tag value from a tag key/value pair

:param kvp: string to extract from
:returns: a tag value string
)TOK")

        .def("kvpToParts", &Tags::kvpToParts, 
R"TOK(
@brief kvpToParts Breaks a KVP string into its constituent parts
:param kvp: a KVP string of the form <key>=<value>
:returns: a list of strings
)TOK")

        .def("hasKvp", &Tags::hasKvp, 
R"TOK(
Returns true if the tags have the specified kvp

:param kvp: kvp to search for; value wildcards are supported using '*'
:returns: true if tags contain the kvp; false otherwise
)TOK")

        .def("hasAnyKvp", &Tags::hasAnyKvp, 
R"TOK(
Returns true if the tags have any key=value in the input list

:param kvps: kvps to search for; value wildcards are supported using '*'
:returns: true if tags contain at least one kvp; false otherwise
)TOK")

        .def("getFirstMatchingKvp", &Tags::getFirstMatchingKvp, 
R"TOK(
Returns the first matching key/value pair (kvp) from the input list

:param kvps: list of kvp string to match; value wildcards are supported using '*'
:returns: a kvp or an empty string if no matching kvp is found
)TOK")

        .def_static("Tags", &Tags::kvpListToTags,
R"TOK(
Converts a list of KVPs into tags

:param kvps: kvps to convert
:returns: a set of tags
)TOK")

        .def("toKvps", &Tags::toKvps,
R"TOK(Returns the tags as key/value pair strings

:returns: a list of key/value pairs
)TOK")

        //.def("toKeys", &Tags::toKeys, 
//R"TOK(
//toKeys returns the tags as a list of key strings
//:returns: a list of key strings
//)TOK")


        .def("hasAnyKey", &Tags::hasAnyKey, 
R"TOK(
Returns true if the tags have any key in the input list

:param keys: tag keys to search for
:returns: true if the tags contain at least one of the keys; false otherwise
)TOK")

        .def("getFirstMatchingKey", &Tags::getFirstMatchingKey, 
R"TOK(
Returns the first tag key found from an input list of keys

:param keys: tag keys to search for
:returns: a non-empty string if any key in the list was found; otherwise an empty string
)TOK")


        .def("schemaVerticesToTags", &Tags::schemaVerticesToTags, 
R"TOK(
Converts a collection of schema vertices to tags

:param vertices: schema vertices to convert
:returns: a set of tags
)TOK")


        .def_static("haveMatchingName", &Tags::haveMatchingName, 
R"TOK(
Determines if two set of tags have a matching name

:param tags1: first set of tags to examine
:param tags2: second set of tags to examine
@parm strictNameMatch if true, will not consider names with the alt_name tag key
:returns: true if the tags have at least one matching name; false otherwise
)TOK")

        .def("hasName", &Tags::hasName, 
R"TOK(
Determines whether a name exists in the set of tag

:returns: true if at least one name exists; false otherwise
)TOK")


        .def_static ("onlyOneContainsKvp", &Tags::onlyOneContainsKvp, 
R"TOK(
Determines if either one of two sets of tags contain a particular key/value pair

:param tags1: first set of tags to examine
:param tags2: second set of tags to examine
:param kvp: key/value pair to search for
:returns: true if exactly one of the sets of tags contain the key/value pair; false otherwise
)TOK")


        .def_static ("bothHaveInformation", &Tags::bothHaveInformation, 
R"TOK(
Determines if two sets of tags contain non-metadata information

:param tags1: first set of tags to examine
:param tags2: second set of tags to examine
:returns: true if both sets of tags contain non-metadata information; false otherwise
)TOK")


        .def_static ("onlyOneHasInformation", &Tags::onlyOneHasInformation, 
R"TOK(
Determines if one of two sets of tags contain non-metadata information

:param tags1: first set of tags to examine
:param tags2: second set of tags to examine
:returns: true if exactly one of sets of tags contain non-metadata information; false otherwise
)TOK")
        ;

    PyBindModule::remapNames(tags);
}

REGISTER_PYHOOT_SUBMODULE(init_Tags)

}
