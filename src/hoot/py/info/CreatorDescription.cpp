/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

// hoot
#include <hoot/core/info/CreatorDescription.h>

// pybind11
#include <pybind11/pybind11.h>

// pyhoot
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

namespace hoot
{

using namespace std;

static void init_CreatorDescription(py::module_& m)
{
  auto creatorDescription = py::class_<CreatorDescription, shared_ptr<CreatorDescription> >
    (m, "CreatorDescription")
    .def("__str__", &CreatorDescription::toString)
    .def_static ("baseFeatureTypeToString", &CreatorDescription::baseFeatureTypeToString, R"TOK(
Converts a base feature type to a string representation

:param t: the feature type to convert
:returns: a string
)TOK")
    .def_static ("stringToBaseFeatureType", &CreatorDescription::stringToBaseFeatureType, R"TOK(
Converts the string representation of a base feature type to an enum

:param s: the string to convert
:returns: a feature type enumeration value
)TOK")
    .def_static ("getFeatureCalcType", &CreatorDescription::getFeatureCalcType, R"TOK(
Returns the physical measurement feature stat calculation type for a base feature type e.g.
an area calc type is returned for polygon features

:param t: the feature type to retrieve the statistics calculation type for
:returns: a feature statistics calculation type enumeration value
)TOK")
    .def("getElementCriterion", &CreatorDescription::getElementCriterion, R"TOK(
Returns a GeometryTypeCriterion instantiation associated with the given feature type

:param t: a feature type
:param map: map used to initialize the criterion
:returns: a GeometryTypeCriterion

@note It would be better to return a ConflatableElementCriterion here instead, but returning
NonBuildingAreaCriterion doesn't allow for that. Doing so also makes this inconsistent with
getElementCriterionName. Think if we change to AreaCriterion, however, that will throw the
stats off.
)TOK")
    .def_static ("getElementCriterionName", &CreatorDescription::getElementCriterionName, R"TOK(
Returns the name of a ConflatableElementCriterion associated with the given feature type

:param t: a feature type
:returns: the class name of a ConflatableElementCriterion
)TOK")
    .def("toString", &CreatorDescription::toString)
    .def("getExperimental", &CreatorDescription::getExperimental)
    .def("getClassName", &CreatorDescription::getClassName)
    .def("getDescription", &CreatorDescription::getDescription)
    .def("getBaseFeatureType", &CreatorDescription::getBaseFeatureType)
    .def("getGeometryType", &CreatorDescription::getGeometryType)
    .def("setExperimental", &CreatorDescription::setExperimental)
    .def("setClassName", &CreatorDescription::setClassName)
    .def("setDescription", &CreatorDescription::setDescription)
    .def("setBaseFeatureType", &CreatorDescription::setBaseFeatureType)
    .def("setGeometryType", &CreatorDescription::setGeometryType)
    .def("setMatchCandidateCriteria", &CreatorDescription::setMatchCandidateCriteria)
  ;
  PyBindModule::remapNames(creatorDescription);

  py::enum_<CreatorDescription::BaseFeatureType>(creatorDescription, "BaseFeatureType", R"TOK(
This is how we map various match creators to the feature they operate on.
Helpful when generating stats later.)TOK")
    .value("POI", CreatorDescription::BaseFeatureType::POI)
    .value("HIGHWAY", CreatorDescription::BaseFeatureType::Highway)
    .value("BUILDING", CreatorDescription::BaseFeatureType::Building)
    .value("RIVER", CreatorDescription::BaseFeatureType::River)
    .value("POIPOLYGONPOI", CreatorDescription::BaseFeatureType::PoiPolygonPOI,
      "This is a superset of POI specific to poi/poly conflation.")
    .value("POLYGON", CreatorDescription::BaseFeatureType::Polygon,
      "Polygon is a superset of building.")
    .value("AREA", CreatorDescription::BaseFeatureType::Area)
    .value("RAILWAY", CreatorDescription::BaseFeatureType::Railway)
    .value("POWERLINE", CreatorDescription::BaseFeatureType::PowerLine)
    .value("POINT", CreatorDescription::BaseFeatureType::Point)
    .value("LINE", CreatorDescription::BaseFeatureType::Line)
    .value("RELATION", CreatorDescription::BaseFeatureType::Relation)
    .value("UNKNOWN", CreatorDescription::BaseFeatureType::Unknown)
    .export_values();

  py::enum_<CreatorDescription::FeatureCalcType>(creatorDescription, "FeatureCalcType")
    .value("CALCTYPENONE", CreatorDescription::FeatureCalcType::CalcTypeNone)
    .value("CALCTYPELENGTH", CreatorDescription::FeatureCalcType::CalcTypeLength)
    .value("CALCTYPEAREA", CreatorDescription::FeatureCalcType::CalcTypeArea)
    .export_values();

}

REGISTER_PYHOOT_SUBMODULE(init_CreatorDescription)

}
