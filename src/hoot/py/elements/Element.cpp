/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>

#include <hoot/core/elements/Element.h>
#include <hoot/core/elements/ElementProvider.h>
#include <hoot/core/elements/Relation.h>
#include <hoot/core/visitors/ConstElementVisitor.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_Element(py::module_& m)
{
  // This is a lazy wrapping of Element. All the functions have been wrapped to some degree but
  // the more difficult functions have been commented out.
  //
  // No new comments have been added but existing hoot comments have been converted to python
  // style docstrings.
  auto element = py::class_<hoot::Element, std::shared_ptr<Element> >(m, "Element")
    .def("__str__", &Element::toString)
    .def("addTags", &Element::addTags)
    .def("clear", &Element::clear)
    .def("clone", &Element::clone)
    .def("getChangeset", &Element::getChangeset)
    .def("getCircularError", &Element::getCircularError, 
R"TOK(
Circular Error is in meters to 2 standard deviations. In other words it is about the 95%
confidence interval assuming a normal distribution.
)TOK")
    .def("getElementId", &Element::getElementId)
    .def("getElementType", &Element::getElementType)
//     .def("getEnvelope", &Element::getEnvelope,
// R"TOK(
// Calculates and returns this element's envelope. Returns a null envelope if this element is
// empty or any of the child elements are missing. The caller gets ownership of the returned
// envelope.
// )TOK")
//     .def("getEnvelopeInternal", &Element::getEnvelopeInternal)
    .def("getId", &Element::getId)
    .def("getRawCircularError", &Element::getRawCircularError)
    .def("getStatus", &Element::getStatus)
    .def("getStatusString", &Element::getStatusString)
    .def("getTag", &Element::getTag)
    .def("getTags", [](const Element& self) { return self.getTags(); })
    .def("getTags", [](Element& self) { return self.getTags(); })
    .def("getTagCount", &Element::getTagCount)
    .def("getTimestamp", &Element::getTimestamp)
    .def("getUid", &Element::getUid)
    .def("getUser", &Element::getUser)
    .def("getVersion", &Element::getVersion)
    .def("getVisible", &Element::getVisible)
    .def("hasCircularError", &Element::hasCircularError)
    .def("hasSameNonMetadataTags", &Element::hasSameNonMetadataTags,
R"TOK(
Compares information tags with another element
:param other: element to compare this element's tags with
:returns: true if this element has the same information tags as the other element;
  false otherwise
)TOK")
    .def("hasTag", [](const Element& self, QString key) { return self.hasTag(key); })
    .def("hasTag", [](const Element& self, QString key, QString value) 
      { return self.hasTag(key, value); })
    .def("isUnknown", &Element::isUnknown)
//     .def("registerListener", &Element::registerListener,
// "At this point only one listener is supported, but we could support more later if needed."
    .def("removeTag", &Element::removeTag)
    .def("setChangeset", &Element::setChangeset)
    .def("setCircularError", &Element::setCircularError)
    .def("setId", &Element::setId)
    .def("setStatus", &Element::setStatus)
    .def("setStatus", [](Element& self, int type) { self.setStatus(type); })
    .def("setTag", &Element::setTag)
    .def("setTags", &Element::setTags)
    .def("setTimestamp", &Element::setTimestamp)
    .def("setUid", &Element::setUid)
    .def("setUser", &Element::setUser)
    .def("setVersion", &Element::setVersion)
    .def("setVisible", &Element::setVisible)
    .def("toString", &Element::toString)
//     .def("visitRo", &Element::visitRo,
// R"
// Applies a read only visitor to this element and all child elements. The visitor will be called
// at least once for each element in the tree. For instance if the Element is a Way it may be
// called twice for a Node if that node appears twice in the way.

// Making changes while visiting will result in undefined behavior.

// Children that do not appear in the map will not be visited. This may happen during distributed
// computations.

// "this" is guaranteed to be visited last.

// :param map: the map to visit
// :param visitor: the visitor to visit with
// :param recursive: if true, child elements are visited
// "
//     .def("visitRw", &Element::visitRw,
// R"visitRw Applies a read write visitor to this element and all child elements. The visitor will be 
// called at least once for each element in the tree. For instance if the Element is a Way it may be
// called twice for a Node if that node appears twice in the way.

// The visitor may change the element that is currently being visited or any of its children. The
// filter should not change any other element. Changing elements while visiting may impact which
// children are visited. The visiting occurs in a depth first fashion.

// Due to the read/write fashion this is slower than the read-only equivalent.

// Children that do not appear in the map will not be visited. This may happen during distributed
// computations.

// "this" is guaranteed to be visited last.

// :param map: the map to visit
// :param visitor: the visitor to visit with
// :param recursive: if true, child elements are visited
    ;
  PyBindModule::remapNames(element);

  // This is a lazy wrapping of Relation. All the functions have been wrapped to some degree but
  // the more difficult functions have been commented out.
  auto relation = py::class_<hoot::Relation, std::shared_ptr<Relation> >(m, "Relation", element)
    .def_static("className", &Relation::className)
    // .def("addElement", &Relation::addElement)
    // .def("addElement", &Relation::addElement)
    // .def("addElement", &Relation::addElement)
    .def("insertElement", &Relation::insertElement, R"TOK(
Inserts a relation member

:param role: role of the member
:param elementId: ID of the member
:param pos: position in the relation to insert the member
)TOK")
//     .def("removeElement", &Relation::removeElement, R"TOK(
// Remove all members that meet the specified criteria. If no members meet the criteria then
// no changes are made.
// )TOK")
//     .def("removeElement", &Relation::removeElement)
//     .def("removeElement", &Relation::removeElement)
//     .def("replaceElement", &Relation::replaceElement, R"TOK(
// Replaces all instances of from in the relation with to. If from is not in the relation then
// no changes are made.
// )TOK")
//     .def("replaceElement", &Relation::replaceElement)
//     .def("replaceElement", &Relation::replaceElement)
    .def("clear", &Relation::clear, R"TOK(
Removes members, tags, type and circularError.
)TOK")
    .def("getMembers", [](const Relation& self) { return self.getMembers(); })
    .def("getMembers", &Relation::getMembers)
    .def("getMemberCount", &Relation::getMemberCount)
    .def("getMember", &Relation::getMember)
    .def("setMembers", &Relation::setMembers)
    .def("contains", &Relation::contains, R"TOK(
Returns true if this relation contains the specified ElementId. This does not recursively
search for the element.
)TOK")
    .def("indexOf", &Relation::indexOf, R"TOK(
Finds the index of a member

:param eid: ID of the relation member
:returns: a numerical index
)TOK")
    .def("memberIdAt", &Relation::memberIdAt, R"TOK(
Retrieves the relation member element at a specified index

:param index: the index to retrieve the element member from
:returns: a valid element, if found; an invalid element otherwise
)TOK")
    .def("isFirstMember", &Relation::isFirstMember, R"TOK(
Determines if the first relation member has a specified ID

:param eid: the element ID to search for
:returns: true if an element having the specified ID is contained at the first relation member
location; false otherwise
)TOK")
    .def("isLastMember", &Relation::isLastMember, R"TOK(
Determines if the last relation member has a specified ID

:param eid: the element ID to search for
:returns: true if an element having the specified ID is contained at the last relation member
location; false otherwise
)TOK")
    .def("getMemberIds", [](const Relation& self) { return self.getMemberIds(); })
    .def("getMemberIds", &Relation::getMemberIds, R"TOK(
Returns the IDs of members

:param elementType: optional element type of element Ids to return
:returns: a collection of element IDs
)TOK")
    .def("getAdjoiningMemberIds", &Relation::getAdjoiningMemberIds, R"TOK(
Retrieves the member element IDs for members placed immediately before and after the member
element with the specified ID

:param memberId: the ID of the member element to retrieve adjoining member element IDs for
:returns: If a member with the specified ID exists 1) and is neither the first nor last member, a
list with two elements IDs where the first ID is the ID of the member element directly
preceding the element with the specified ID and the second ID is the ID of the member directly
succeeding the element with the specified ID. 2) and is the first member, a list with one
element ID where the ID is the ID of the member directly succeeding the element with the
specified ID. 3) and is the last member, a list with one element ID where the ID is the ID of
the member directly preceding the element with the specified ID. If the relation contains no
member with the specified ID, then an empty list is returned.
)TOK")
    .def("numElementsByRole", &Relation::numElementsByRole, R"TOK(
Returns the number of member elements with the given relation role

:param role: role by which to examine elements
:returns: the number of member elements with the specified role
)TOK")
    .def("getElementsByRole", &Relation::getElementsByRole, R"TOK(
Retrieves all members with a particular role

:param role: role to search for
:returns: a collection of members
)TOK")
    .def("getRole", &Relation::getRole)
    .def("getEnvelope", &Relation::getEnvelope)
    .def("getEnvelopeInternal", &Relation::getEnvelopeInternal)
    .def("getElementType", &Relation::getElementType)
    .def("getType", &Relation::getType)
    .def("isMultiPolygon", &Relation::isMultiPolygon, R"TOK(
Returns true if this is a multipolygon type. No checking is done to determine if the geometry
is valid.
)TOK")
    .def("isReview", &Relation::isReview, R"TOK(
Returns true if this is a review.
)TOK")
    .def("isRestriction", &Relation::isRestriction)
    .def("setType", &Relation::setType, R"TOK(
Sets the "type" of the relation. See the OSM wiki [1] for a detailed description. Example
types include "building", "multipolygon" and "multilinestring".

1. http://wiki.openstreetmap.org/wiki/Relation
)TOK")
    .def("toString", &Relation::toString)
    .def("visitRo", &Relation::visitRo, R"TOK(
@see Element
)TOK")
    .def("visitRw", &Relation::visitRw, R"TOK(
@see Element
)TOK")
    ;
  PyBindModule::remapNames(relation);
}

REGISTER_PYHOOT_SUBMODULE(init_Element)

}
