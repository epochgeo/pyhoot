/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <pybind11/pybind11.h>

#include <hoot/core/info/Version.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

const char* version() {
    return hoot::Version::getFullVersion();
}

// PYBIND11_MODULE(libpyhoot, m) {
//     m.doc() = "pybind11 example plugin"; // optional module docstring

//     m.def("add", &add, "A function which adds two numbers");
//     m.def("version", &hoot::Version::getFullVersion, "get hoot version");

//     init_Factory(m);
    
//     py::class_<hoot::Version>(m, "Version")
//         .def_static("getFullVersion", &hoot::Version::getFullVersion);
// }

