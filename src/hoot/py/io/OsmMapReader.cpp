/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/io/OsmMapReader.h>
#include <hoot/core/io/OsmJsonReader.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_OsmMapReader(py::module_& m)
{
  auto osmMapReader = py::class_<OsmMapReader, std::shared_ptr<OsmMapReader> >(m, "OsmMapReader")
    .def("isSupported", &OsmMapReader::isSupported, R"TOK(
Returns true if the output URL is likely supported. This won't necessarily do an exhaustive
check. It will look to see if the URL is properly formatted (e.g. ends in .osm, or starts
with postgresql:, etc.)
)TOK")
    .def("open", &OsmMapReader::open, R"TOK(
Opens the specified URL for reading.
)TOK")
    .def("read", &OsmMapReader::read, R"TOK(
Reads the specified map. When this method is complete the input will likely be closed.
)TOK")
    .def("setDefaultStatus", &OsmMapReader::setDefaultStatus, R"TOK(
Determines the reader's default element status
)TOK")
    .def("setUseDataSourceIds", &OsmMapReader::setUseDataSourceIds, R"TOK(
Determines whether the reader should use the element id's from the data being read
)TOK")
    .def("setUseFileStatus", &OsmMapReader::setUseFileStatus, R"TOK(
Uses the element status from the file
)TOK")
    .def("supportedFormats", &OsmMapReader::supportedFormats, R"TOK(
Lists supported data format extensions

If multiple are supported, delimit them with a semicolon.

:returns: a formats string
)TOK")
    .def("setConfiguration", &OsmMapReader::setConfiguration, R"TOK( Configurable interface)TOK")
    .def("getIgnoreDuplicates", &OsmMapReader::getIgnoreDuplicates, R"TOK(
Gets the ignore duplicates flag
)TOK")
    .def("setIgnoreDuplicates", &OsmMapReader::setIgnoreDuplicates, R"TOK(
Set the ignore duplicates flag, when set to true, derived classes will ignore any element
who's ID is already being used.  This is useful when elements cross bounding box boundaries
and multiple bounding boxes are being merged together.
)TOK")
    .def("setWarnOnVersionZeroElement", &OsmMapReader::setWarnOnVersionZeroElement)
  ;

  PyBindModule::remapNames(osmMapReader);

  auto osmJsonReader = py::class_<OsmJsonReader, std::shared_ptr<OsmJsonReader> >
    (m, "OsmJsonReader", osmMapReader)
    .def(py::init<>())
    .def("loadFromString", &OsmJsonReader::loadFromString, R"TOK(
loadFromString - Builds a map from the JSON string. Throws a
       HootException with error and line number if JSON parsing fails
:param jsonStr: - input string, map - The OSM map to load it into
)TOK")
    .def("loadFromFile", &OsmJsonReader::loadFromFile, R"TOK(
loadFromFile - Reads the whole file as a string, passes it
       to loadFromString()
:param path: - Path to file
:returns: Smart pointer to the OSM map
)TOK")
//     .def_static("scrubQuotes", &OsmJsonReader::scrubQuotes, R"TOK(
// scrubQuotes Converts single quotes to double quotes, and escaped
//         apostrophes to regular apostrophes
// :param jsonStr: proper JSON string
// )TOK")
//     .def_static("scrubBigInts", &OsmJsonReader::scrubBigInts, R"TOK(
// scrubBigInts Ensures that we have quotes around big integers.
//        Numbers > 2^31 seem to cause trouble with the boost property_tree
//        json parser in boost 1.41
// :param jsonStr: string upon which we operate
// )TOK")
    .def("supportedFormats", &OsmJsonReader::supportedFormats)
    .def("setConfiguration", &OsmJsonReader::setConfiguration, R"TOK(
Set the configuration for this object.
)TOK")
    .def("isValidJson", &OsmJsonReader::isValidJson)
    .def("getVersion", &OsmJsonReader::getVersion, R"TOK(
getVersion Overpass API version, if that's where JSON comes from
:returns: version string
)TOK")
    .def("getGenerator", &OsmJsonReader::getGenerator, R"TOK(
getGenerator Map generator name, if supplied in JSON
:returns: generator name string
)TOK")
    .def("getTimestampBase", &OsmJsonReader::getTimestampBase, R"TOK(
getTimestampBase OSM timestamp base, if supplied in JSON
:returns: timestamp base string
)TOK")
    .def("getCopyright", &OsmJsonReader::getCopyright, R"TOK(
getCopyright Copyright statement, if supplied in JSON
:returns: copyright string
)TOK")
    .def("setKeepImmediatelyConnectedWaysOutsideBounds",
      &OsmJsonReader::setKeepImmediatelyConnectedWaysOutsideBounds)
    .def("setLogWarningsForMissingElements", &OsmJsonReader::setLogWarningsForMissingElements)
  ;

  PyBindModule::remapNames(osmJsonReader);
}

REGISTER_PYHOOT_SUBMODULE(init_OsmMapReader)

}
