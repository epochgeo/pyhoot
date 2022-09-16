/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/algorithms/rubber-sheet/RubberSheet.h>
#include <hoot/core/conflate/IdSwap.h>
#include <hoot/core/conflate/highway/Roundabout.h>
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/elements/OsmMapListener.h>
#include <hoot/core/index/OsmMapIndex.h>
#include <hoot/core/visitors/ElementVisitor.h>
#include <hoot/core/visitors/ConstElementVisitor.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

namespace hoot
{

using RwVisitFunction = std::function<void(const ElementPtr& element)>;

void init_OsmMap(py::module_& m)
{
  auto wrapme = py::class_<OsmMap, std::shared_ptr<OsmMap> >(m, "OsmMap")
    .def(py::init([]() { return OsmMapPtr(new OsmMap()); }))
    .def("getElement",
        static_cast<ElementPtr (OsmMap::*)(const ElementId&)>(&OsmMap::getElement),
        "getElement returns an element by ElementId")
    .def("getElement",
        static_cast<ElementPtr (OsmMap::*)(ElementType type, long id)>(&OsmMap::getElement),
        "getElement returns an element by element type and id")
//    .def("addElements", &OsmMap::addElements)
    .def("getElementCount", &OsmMap::getElementCount)
    .def("size", &OsmMap::size)
//    .def("containsElement", &OsmMap::containsElement, R"TOK(
//Returns true if an element with the specified type/id exists.
//Throws an exception if the type is unrecognized.
//)TOK")
    //.def("containsElement", &OsmMap::containsElement)
    //.def("containsElement", &OsmMap::containsElement)
    .def("visitRo", &OsmMap::visitRo, R"TOK(
Calls the visitRo method on all elements. See Element::visitRo for a more
thorough description.
 - The order will always be nodes, ways, relations, but the IDs will not
   be in any specific order.
 - Unlike Element::visitRo, elements will not be visited multiple times.
 - Modifying the OsmMap while traversing will result in undefined behaviour.
 - This should be slightly faster than visitRw.

If the visitor implements OsmMapConsumer then setOsmMap will be called before visiting any
elements.
)TOK")
    .def("visitRw", [](OsmMap& self, ElementVisitor& v) { self.visitRw(v); },
R"TOK(
Calls the visitRw method on all elements. See Element::visitRw for a more
thorough description.
 - The order will always be nodes, ways, relations, but the IDs will not
   be in any specific order.
 - Elements that are added during the traversal may or may not be visited.
 - Elements may be deleted during traversal.
 - The visitor is guaranteed to not visit deleted elements.

If the visitor implements OsmMapConsumer then setOsmMap will be called before
visiting any elements.
)TOK")
//    .def("visitRw", [](OsmMap& self, RwVisitFunction func) {

//    })
    .def("visitRw", [](OsmMap& self, ConstElementVisitor& v) { self.visitRw(v); })
//    .def("replace", &OsmMap::replace, R"TOK(
//Replace the all instances of from with instances of to. In some cases this may be an invalid
//operation and an exception will be throw. E.g. replacing a node with a way where the node
//is part of another way.
//)TOK")
//    .def("replace", &OsmMap::replace, R"TOK(
//Similar to above, but from is replaced with a collection of elements. This makes sense in the
//context of a relation, but may not make sense in other cases (e.g. replace a single node
//that is part of a way with multiple nodes).
//)TOK")
  /////////////////////////////////////NODE//////////////////////////////////////////////
//    .def("getNode", &OsmMap::getNode)
//    .def("getNode", &OsmMap::getNode)
//    .def("getNode", &OsmMap::getNode)
//    .def("getNode", &OsmMap::getNode)
    .def("getNodes", [](OsmMap& self) {
      return std::map<long, ElementPtr>(self.getNodes().begin(), self.getNodes().end());
    })
    .def("getNodeIds", &OsmMap::getNodeIds)
    .def("getNodeCount", &OsmMap::getNodeCount)
    .def("containsNode", &OsmMap::containsNode, R"TOK(
Returns true if the node is in this map.
)TOK")
    .def("addNode", &OsmMap::addNode)
    .def("addNodes", &OsmMap::addNodes, R"TOK(
Add all the nodes in the provided vector. This can be faster than calling addNode multiple
times.
)TOK")
    .def("replaceNode", &OsmMap::replaceNode, R"TOK(
Intelligently replaces all instances of oldNode with newNode. This looks at all the ways
for references to oldNode and replaces those references with newNode. Finally, oldNode is
removed from this OsmMap entirely.
)TOK")
    .def("createNextNodeId", &OsmMap::createNextNodeId)
    .def("visitNodesRo", &OsmMap::visitNodesRo)
    //.def("visitNodesRw", &OsmMap::visitNodesRw)
    .def("numNodesAppended", &OsmMap::numNodesAppended)
    .def("numNodesSkippedForAppending", &OsmMap::numNodesSkippedForAppending)
  ///////////////////////////////////////WAY////////////////////////////////////////////////

//    .def("getWay", &OsmMap::getWay, R"TOK(
//Return the way with the specified id or null if it doesn't exist.
//)TOK")
//    .def("getWay", &OsmMap::getWay)
//    .def("getWay", &OsmMap::getWay, R"TOK(
//Similar to above but const'd.

//We can't return these values by reference b/c the conversion from non-const to const requires
//a copy. The copy would be a temporary variable if we returned a reference which creates some
//weirdness and a warning.
//)TOK")
//    .def("getWay", &OsmMap::getWay)
    .def("getWays", &OsmMap::getWays)
    .def("getWayIds", &OsmMap::getWayIds)
    .def("getWayCount", &OsmMap::getWayCount)
    .def("addWay", &OsmMap::addWay)
    .def("containsWay", &OsmMap::containsWay)
    .def("createNextWayId", &OsmMap::createNextWayId)
    .def("visitWaysRo", &OsmMap::visitWaysRo)
    .def("visitWaysRw", &OsmMap::visitWaysRw)
    .def("numWaysAppended", &OsmMap::numWaysAppended)
    .def("numWaysSkippedForAppending", &OsmMap::numWaysSkippedForAppending)
  ////////////////////////////////////////RELATION/////////////////////////////////////////////////
//    .def("getRelation", &OsmMap::getRelation)
//    .def("getRelation", &OsmMap::getRelation)
//    .def("getRelation", &OsmMap::getRelation)
    .def("getRelations", &OsmMap::getRelations)
    .def("getRelationIds", &OsmMap::getRelationIds)
    .def("getRelationCount", &OsmMap::getRelationCount)
    .def("addRelation", &OsmMap::addRelation)
    .def("containsRelation", &OsmMap::containsRelation)
    .def("createNextRelationId", &OsmMap::createNextRelationId)
    .def("visitRelationsRo", &OsmMap::visitRelationsRo)
    .def("visitRelationsRw", &OsmMap::visitRelationsRw)
    .def("numRelationsAppended", &OsmMap::numRelationsAppended)
    .def("numRelationsSkippedForAppending", &OsmMap::numRelationsSkippedForAppending)
  /////////////////////////////////////////////////////////////////////////////////////

    .def("append", &OsmMap::append, R"TOK(
Append all the elements in input map to this map.

The default behavior is to skip an element from the map being appended from if it has the same
ID as an element in this map and the elements are considered identical. If the elements are
considered to be identical, an error occurs. Alternatively, the throwOutDupes parameter will
allow for overriding that behavior at the expense of not appending the elements.

:param map
@param: throwOutDupes if true, and elements in the map being appended from have the same IDs as
elements in this map, those elements are ignored
@throws if there is element ID overlap and throwOutDupes = false
@throws if the map being appended to is the same as the map being appended from
@throws if the map being appended to does not have the same projection as the map being
appended from
)TOK")
    .def("clear", &OsmMap::clear)
    .def("isEmpty", &OsmMap::isEmpty)
    .def("validate", &OsmMap::validate, R"TOK(
Validates the consistency of the map. Primarily this checks to make sure that all nodes
referenced by a way exist in the map. A full dump of all invalid ways is logged before the
function throws an error.
:param strict: If true, the method throws an exception rather than returning a result if the
              validation fails.
:returns: True if the map is valid, false otherwise.
)TOK")
    .def("getParents", &OsmMap::getParents)
    .def("getProjection", &OsmMap::getProjection, R"TOK(
Returns the SRS for this map. The SRS should never be changed and defaults to WGS84.
)TOK")
    .def("registerListener", &OsmMap::registerListener)
    .def_static("resetCounters", &OsmMap::resetCounters, R"TOK(
Resets the way and node counters. This should ONLY BE CALLED BY UNIT TESTS.
)TOK")
    .def("appendSource", &OsmMap::appendSource)
    .def("replaceSource", &OsmMap::replaceSource)
    .def("resetIterator", &OsmMap::resetIterator)
    .def("getIndex", &OsmMap::getIndex, R"TOK(
This returns an index of the OsmMap. Adding or removing ways from the map will make the index
out of date and will require calling getIndex again.
)TOK")
    .def("getListeners", &OsmMap::getListeners)
    .def("getIdGenerator", &OsmMap::getIdGenerator)
    .def("getSource", &OsmMap::getSource)
    .def("getRoundabouts", &OsmMap::getRoundabouts)
    .def("getIdSwap", &OsmMap::getIdSwap)
    .def("getName", &OsmMap::getName)
    .def("setName", &OsmMap::setName)
    .def("setIdSwap", &OsmMap::setIdSwap)
    .def("setRoundabouts", &OsmMap::setRoundabouts)
    .def("setProjection", &OsmMap::setProjection)
    .def("setEnableProgressLogging", &OsmMap::setEnableProgressLogging)
    .def("setCachedRubberSheet", &OsmMap::setCachedRubberSheet)
    .def("getCachedRubberSheet", &OsmMap::getCachedRubberSheet)
    .def("setIdGenerator", &OsmMap::setIdGenerator)

  ;
  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_OsmMap)

}
