/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/io/OsmMapWriter.h>
#include <hoot/core/io/OsmJsonWriter.h>
#include <hoot/core/io/OsmXmlWriter.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_OsmMapWriter(py::module_& m)
{
  auto osmMapWriter = py::class_<OsmMapWriter, std::shared_ptr<OsmMapWriter> >(m, "OsmMapWriter")
    .def("isSupported", &OsmMapWriter::isSupported, R"TOK(
Returns true if the output URL is likely supported. This won't necessarily do an exhaustive
check. It will look to see if the URL is properly formatted (e.g. ends in .osm, or starts
with postgresql:, etc.)
)TOK")
    .def("open", &OsmMapWriter::open, R"TOK(
Opens the specified URL for writing.
)TOK")
    .def("write", &OsmMapWriter::write, R"TOK(
Writes the specified map out. When this method is complete the output will likely be closed
and all data is guaranteed to be flushed.
)TOK")
    .def("supportedFormats", &OsmMapWriter::supportedFormats, R"TOK(
Lists supported data format extensions

If multiple are supported, delimit them with a semicolon.

:returns: a formats string
)TOK")
    .def("getIsDebugMap", &OsmMapWriter::getIsDebugMap, R"TOK(
Gets flag indicating the writer is writing a debug map so that extra debugging metadata can
be included in each implementation of the output formats
)TOK")
    .def("setIsDebugMap", &OsmMapWriter::setIsDebugMap, R"TOK(
Sets flag indicating the writer is writing a debug map so that extra debugging metadata is
included in the output
)TOK")
  ;

  PyBindModule::remapNames(osmMapWriter);

  auto osmJsonWriter = py::class_<OsmJsonWriter, std::shared_ptr<OsmJsonWriter> >
    (m, "OsmJsonWriter", osmMapWriter)
    .def(py::init<>())
    .def("setConfiguration", &OsmJsonWriter::setConfiguration)
    .def("isSupported", &OsmJsonWriter::isSupported)
    .def("open", &OsmJsonWriter::open)
    .def("close", &OsmJsonWriter::close)
    .def("write", [](OsmJsonWriter& self, const ConstOsmMapPtr& osmMap) { self.write(osmMap); })
    .def("supportedFormats", &OsmJsonWriter::supportedFormats)
    .def_static ("markupString", &OsmJsonWriter::markupString, R"TOK(
Mark up a string so it can be used in JSON. This will add double quotes around the string too.
)TOK")
    .def("toString", &OsmJsonWriter::toString, R"TOK(
Very handy for testing.
)TOK")
    .def("setPrecision", &OsmJsonWriter::setPrecision)
    .def("setIncludeCompatibilityTags", &OsmJsonWriter::setIncludeCompatibilityTags)
    .def("setIncludeCircularError", &OsmJsonWriter::setIncludeCircularError)
  ;

  PyBindModule::remapNames(osmJsonWriter);

  auto osmXmlWriter = py::class_<OsmXmlWriter, std::shared_ptr<OsmXmlWriter> >
    (m, "OsmXmlWriter", osmMapWriter)
    .def(py::init<>())
    .def("isSupported", &OsmXmlWriter::isSupported)
    .def("open", &OsmXmlWriter::open)
    .def("close", &OsmXmlWriter::close)
    .def("write", [](OsmXmlWriter& self, const ConstOsmMapPtr& osmMap) { self.write(osmMap); })
    .def("supportedFormats", &OsmXmlWriter::supportedFormats)
    .def_static("toString", &OsmXmlWriter::toString, R"TOK(
Write the map out to a string and return it. This is handy for debugging, but has obvious
memory limitations with real data.

:param map: the map to write out as a string
:param formatXml: if true, formats the xml with indentations and new lines
:returns: an OSM XML string
)TOK",
      py::arg("map"),
      py::arg("format_xml") = true)
    .def("setPrecision", &OsmXmlWriter::setPrecision)
    .def("setIncludeCompatibilityTags", &OsmXmlWriter::setIncludeCompatibilityTags)
  ;

  PyBindModule::remapNames(osmXmlWriter);
}

REGISTER_PYHOOT_SUBMODULE(init_OsmMapWriter)

}
