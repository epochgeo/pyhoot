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
    .def("getTags", static_cast<Tags& (Element::*)()>(&Element::getTags))
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
}

REGISTER_PYHOOT_SUBMODULE(init_Element)

}
