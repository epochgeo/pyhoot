/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#include <boost/noncopyable.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// hoot includes
#include <hoot/core/util/Factory.h>

// pyhoot includes
#include <hoot/py/bindings/PyBindModule.h>
#include <hoot/py/bindings/QtBindings.h>

namespace py = pybind11;

using namespace hoot;

namespace hoot
{

void init_Factory(py::module_& m)
{
    auto factory = py::class_<hoot::Factory, std::unique_ptr<Factory, py::nodelete> >(m, "Factory")
        .def(py::init([]() { return &Factory::getInstance(); }))
        .def_static("getObjectNamesByBase",
            [](const QString& base) {
                std::vector<std::string> result;
                std::vector<QString> convertMe = Factory::getInstance().getObjectNamesByBase(base);
                for (size_t i = 0; i < convertMe.size(); i++)
                {
                    result.push_back(convertMe[i].toStdString());
                }
                return result;
            },
            "returns all registered classes that implement the given base class"
        );

    PyBindModule::remapNames(factory);
}

REGISTER_PYHOOT_SUBMODULE(init_Factory)

}
