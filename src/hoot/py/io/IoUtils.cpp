/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/io/IoUtils.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_IoUtils(py::module_& m)
{
  auto wrapme = py::class_<IoUtils, std::shared_ptr<IoUtils> >(m, "IoUtils")
    .def_static("className", &IoUtils::className)
    .def_static("isSupportedInputFormat", &IoUtils::isSupportedInputFormat, R"TOK(
Determines if the a URL is a supported input format

:param url: the URL to examine
:returns: true if the URL points to a valid input format; false otherwise
)TOK")
    .def_static("isSupportedOutputFormat", &IoUtils::isSupportedOutputFormat, R"TOK(
Determines if the a URL is a supported output format

:param url: the URL to examine
:returns: true if the URL points to a valid output format; false otherwise
)TOK")
    .def_static("isSupportedOsmFormat", &IoUtils::isSupportedOsmFormat, R"TOK(
Returns true if the input format is a Hootenanny supported OSM format

:param input: input path
:returns: true if the input is OSM and supported; false otherwise
)TOK")
    .def_static("isSupportedOgrFormat", &IoUtils::isSupportedOgrFormat, R"TOK(
Returns true if the input format is a Hootenanny supported OGR format

:param input: input path
:param allowDir: if true; then a directory can be passed as an input
:returns: true if the input is supported by OGR; false otherwise
)TOK")
    .def_static("areSupportedOgrFormats", &IoUtils::areSupportedOgrFormats, R"TOK(
Determines if a set of inputs paths are all OGR supported formats

:param inputs: input paths
:param allowDir: if true; then a directory can be passed as an input
:returns: true if all inputs passed in are supported by OGR; false otherwise
)TOK")
    .def_static("anyAreSupportedOgrFormats", &IoUtils::anyAreSupportedOgrFormats, R"TOK(
Determines if any in a set of inputs paths are OGR supported formats

:param inputs: input paths
:param allowDir: if true; then a directory can be passed as an input
:returns: true if any of the inputs passed in are supported by OGR; false otherwise
)TOK")
    .def_static("ogrPathsAndLayersToPaths", &IoUtils::ogrPathsAndLayersToPaths, R"TOK(
Converts the OGR inputs with layer syntax to just the inputs

:param inputs: the inputs to convert
:returns: a list of paths
)TOK")
    .def_static("ogrPathAndLayerToPath", &IoUtils::ogrPathAndLayerToPath, R"TOK(
Converts the OGR input with layer syntax to the input path

:param input: the input to convert
:returns: a path
)TOK")
    .def_static("ogrPathAndLayerToLayer", &IoUtils::ogrPathAndLayerToLayer, R"TOK(
Converts the OGR input with layer syntax to the layer

:param input: the input to convert
:returns: a layer name
)TOK")
    .def_static("getSupportedInputsRecursively", &IoUtils::getSupportedInputsRecursively, R"TOK(
Returns all file paths under a directory point to a supported input format

:param topLevelPaths: one or more directory paths
:param nameFilters: wildcard filters for path exclusion; e.g. *myFile*, *.json
:returns: a list of file paths
)TOK")
    .def_static("expandInputs", &IoUtils::expandInputs, R"TOK(
Returns all valid input file paths expanding any paths by looking inside of VSI files

:param inputs: one or more input files
:returns: a list of file paths
)TOK")
    .def_static("isStreamableIo", &IoUtils::isStreamableIo, R"TOK(
Determines whether both input and output are streamable data sources (associated
readers/writers must implemented the partial map interfaces)

:param input: data source
:param output: data destination
:returns: true if both formats are streamable; false otherwise
)TOK")
    .def_static("areStreamableIo", &IoUtils::areStreamableIo, R"TOK(
Determines whether both inputs and output are streamable data sources (associated
readers/writers must implemented the partial map interfaces)

:param inputs: data sources
:param output: data destination
:returns: true if all formats are streamable; false otherwise
)TOK")
    .def_static("areStreamableInputs", &IoUtils::areStreamableInputs, R"TOK(
Determines whether inputs and are streamable data sources (associated
readers/writers must implemented the partial map interfaces)

:param inputs: data sources
:param logUnstreamable: if true, a message is logged to indicate the input being parsed is not
a streamable input
:returns: true if all inputs are streamable; false otherwise
)TOK")
    .def_static("areValidStreamingOps", &IoUtils::areValidStreamingOps, R"TOK(
Return true if all the specified operations are valid streaming operations.

There are some ops that require the whole map be available in RAM (e.g. remove duplicate
nodes). These operations are not applicable for streaming.

:param ops: class names of operation to determine streamability of
:returns: true if all inputs represent streamable operations; false otherwise
)TOK")
    .def_static("toStreamingOps", &IoUtils::toStreamingOps, R"TOK(
toStreamingOps returns a list of instantiated streaming operation objects
:param ops: the class names of the operations to instantiate
:returns: a list of instantiated visitor objects (OsmMapOperations are not streamable)
@throws IllegalArgumentException if a class name is passed in that does not represent a
streamable operation (not ElementVisitor or ConstElementVisitor) or a class name represents a
class that is an OsmMap consumer (implements OsmMapConsumer or ConstOsmMapConsumer)
)TOK")
    .def_static("isStreamableInput", &IoUtils::isStreamableInput, R"TOK(
Determines if a URL points to a valid streamable input

:param url: the URL to examine
:returns: true if the URL points to a valid streamable input; false otherwise
)TOK")
    .def_static("isStreamableOutput", &IoUtils::isStreamableOutput, R"TOK(
Determines if a URL points to a valid streamable output

:param url: the URL to examine
:returns: true if the URL points to a valid streamable output; false otherwise
)TOK")
    .def_static("getFilteredInputStream", &IoUtils::getFilteredInputStream, R"TOK(
Get an input stream set up to be filtered by operations

:param streamToFilter: the stream to be filtered
:param ops: a list of Hoot operation class names to use for inline filtering on the input stream
:returns: an input stream
)TOK")
    .def_static("loadMap", &IoUtils::loadMap, R"TOK(
    Loads an OSM map into an OsmMap object

    :param map: the object to load the map into
    :param path: the file path to load the map from
    :param useFileId: if true, uses the element ID's in the map file; otherwise, generates new
    element ID's
    :param defaultStatus: the hoot status to assign to all elements
    :param translationScript: script used to translate data; required only if the input is an OGR
    format; ignored otherwise
    :param ogrFeatureLimit: limit of features to read per input; applicable to OGR inputs only;
    ignored otherwise
    :param jobSource: job name for status reporting; applicable to OGR inputs only; ignored otherwise
    :param numTasks: number of job tasks being performed for status reporting; applicable to OGR
    inputs only; ignored otherwise
)TOK",
      py::arg("map"),
      py::arg("path"),
      py::arg("useFileId") = true,
      py::arg("defaultStatus") = Status(Status::Invalid),
      py::arg("translationScript") = QString(),
      py::arg("ogrFeatureLimit") = -1,
      py::arg("jobSource") = QString(),
      py::arg("numTasks") = -1
      )
    .def_static("loadMaps", &IoUtils::loadMaps, R"TOK(
    Loads multiple OSM maps into an OsmMap object

    :param map: the object to load the map into
    :param paths: the file paths to load the maps from
    :param useFileId: if true, uses the element ID's in the map file; otherwise, generates new
    element ID's
    :param defaultStatus: the hoot status to assign to all elements
    :param translationScript: script used to translate data; required only if the input is an OGR
    format; ignored otherwise
    :param ogrFeatureLimit: limit of features to read per input; applicable to OGR inputs only;
    ignored otherwise
    :param jobSource: job name for status reporting; applicable to OGR inputs only; ignored otherwise
    :param numTasks: number of job tasks being performed for status reporting; applicable to OGR
    inputs only; ignored otherwise
)TOK")
    .def_static("saveMap", &IoUtils::saveMap, R"TOK(
    Saves an OSM map to an OsmMap object

    :param map: the map object to save
    :param path: the file path to save the map to
)TOK")
//    .def_static("cropToBounds", &IoUtils::cropToBounds, R"TOK(
//Crops a map to a given bounds

//:param map: the map to crop
//:param bounds: the bounds to crop to
//:param keepConnectedOobWays: if true any way falling outside of the bounds but directly
//connected to a way within the bounds will be kept
//)TOK")
//    .def_static("cropToBounds", &IoUtils::cropToBounds, R"TOK(
//Crops a map to a given bounds

//:param map: the map to crop
//:param bounds: the bounds to crop to
//:param keepConnectedOobWays: if true any way falling outside of the bounds but directly
//connected to a way within the bounds will be kept
//)TOK")
    .def_static("isUrl", &IoUtils::isUrl, R"TOK(
Determines if an input string is a URL by the hoot definition

:param str: string to examine
:returns: true if the input is a hoot URL, false otherwise
)TOK")
    .def_static("writeOutputDir", &IoUtils::writeOutputDir, R"TOK(
Writes an output directory

:param dirName: name of the directory to write
)TOK")
    .def_static("getOutputUrlFromInput", &IoUtils::getOutputUrlFromInput, R"TOK(
Creates an output URL based on an input URL that will not overwrite the input

:param inputUrl: the input URL to generate an output URL for
:param appendText: optional text to append to the output URL; not optional if outputFormat is
not specified
:param outputFormat: optional output format made up of a file extension (e.g. osm) or a custom
output directory extension (e.g. shp); not option if appendText is not specified
:returns: a URL
)TOK")
  ;

  PyBindModule::remapNames(wrapme);
}

REGISTER_PYHOOT_SUBMODULE(init_IoUtils)

}
