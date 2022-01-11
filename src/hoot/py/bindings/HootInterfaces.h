/**
 * MIT License
 * https://opensource.org/licenses/MIT
 *
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */
#ifndef HOOTINTERFACES_H
#define HOOTINTERFACES_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <hoot/core/algorithms/extractors/AbstractDistanceExtractor.h>
#include <hoot/core/algorithms/string/StringDistanceConsumer.h>
#include <hoot/core/elements/ConstOsmMapConsumer.h>
#include <hoot/core/util/Configurable.h>
#include <hoot/core/util/Settings.h>

#include <hoot/py/bindings/QtBindings.h>
#include <hoot/py/bindings/PyBindModule.h>

namespace py = pybind11;

// This file contains wrappers for a number of common hoot interfaces. All classes are templates
// so you can simply call registerSubclass and all relevant interfaces will be wrapped.
namespace hoot
{

using ConstOsmMapPtr = std::shared_ptr<const OsmMap>;
using ConstAbstractDistanceExtractorPtr = std::shared_ptr<const AbstractDistanceExtractor>;

////
// Wrap class with AbstractDistanceExtractor, if appropriate
////
template<class T, typename Wrapper,
  typename std::enable_if<!std::is_base_of<AbstractDistanceExtractor, T>::value, T>::type* = nullptr
>
void wrapAbstractDistanceExtractor(Wrapper& wrapper) {}

template<class T, typename Wrapper,
  typename std::enable_if<std::is_base_of<AbstractDistanceExtractor, T>::value, T>::type* = nullptr
>
void wrapAbstractDistanceExtractor(Wrapper& wrapper)
{
  wrapper
    .def("combinedEnvelopeDiagonalDistance", &T::combinedEnvelopeDiagonalDistance)
    // EuclideanDistanceExtractor has an overload of this so we must specify which one we want
    .def("distance", [](T& self,
        const OsmMap& map, const ConstElementPtr& target, const ConstElementPtr& candidate) {
      return self.distance(map, target, candidate);
    })
  ;
}

////
// Wrap class with Configurable, if appropriate
////
template<class T, typename Wrapper,
  typename std::enable_if<!std::is_base_of<Configurable, T>::value, T>::type* = nullptr
>
void wrapConfigurable(Wrapper& wrapper) {}

template<class T, typename Wrapper,
  typename std::enable_if<std::is_base_of<Configurable, T>::value, T>::type* = nullptr
>
void wrapConfigurable(Wrapper& wrapper)
{
  wrapper
    .def("setConfiguration", &T::setConfiguration,
      "Set the configuration for this object.")
    .def(py::init([](Settings& settings) {
      T* result = new T();
      result->setConfiguration(settings);
      return result;
    }))
    .def(py::init([](std::map<QString, QString> kvps) {
      Settings settings;
      for (auto kvp : kvps)
      {
        settings.set(kvp.first, kvp.second);
      }
      T* result = new T();
      result->setConfiguration(settings);
      return result;
    }), R"TOK(
This constructor takes a Python dict of strings and uses it to initialize the set_configuration
function.
)TOK")
  ;
}

////
// Wrap class with ConstOsmMapConsumer, if appropriate
////
template<class T, typename Wrapper,
  typename std::enable_if<!std::is_base_of<ConstOsmMapConsumer, T>::value, T>::type* = nullptr
>
void wrapConstOsmMapConsumer(Wrapper& wrapper) {}

template<class T, typename Wrapper,
  typename std::enable_if<std::is_base_of<ConstOsmMapConsumer, T>::value, T>::type* = nullptr
>
void wrapConstOsmMapConsumer(Wrapper& wrapper)
{
  wrapper
    .def("setOsmMap", &T::setOsmMap)
    // this isn't explicit in the interface but it is the convention.
    .def(py::init([](ConstOsmMapPtr map) {
      T* result = new T();
      result->setOsmMap(map.get());
      return result;
    }))
  ;
}

////
// Wrap class with StringDistanceConsumer, if appropriate
////
template<class T, typename Wrapper,
  typename std::enable_if<
    std::__not_<
      std::is_base_of<StringDistanceConsumer, T>
    >::value,
    T
  >::type* = nullptr
>
void wrapStringDistanceConsumer(Wrapper& wrapper) {}

template<class T, typename Wrapper,
  typename std::enable_if<std::is_base_of<StringDistanceConsumer, T>::value, T>::type* = nullptr
>
void wrapStringDistanceConsumer(Wrapper& wrapper)
{
  wrapper
    .def("setStringDistance", &T::setStringDistance)
    // this isn't explicit in the interface but it is the convention.
    .def(py::init([](const StringDistancePtr& sd) {
      T* result = new T();
      result->setStringDistance(sd);
      return result;
    }))
  ;
}

////
// Wrap class with StringDistanceConsumer, if appropriate
////
template<class T, typename Wrapper,
  typename std::enable_if<
      std::__or_<
        std::__not_<std::is_base_of<StringDistanceConsumer, T> >,
        std::__not_<std::is_base_of<Configurable, T> >
      >::value,
      T
  >::type* = nullptr
>
void wrapStringDistanceConsumerAndConfigurable(Wrapper& wrapper) {}

template<class T, typename Wrapper,
  typename std::enable_if<
      std::__and_<
        std::is_base_of<StringDistanceConsumer, T>,
        std::is_base_of<Configurable, T>
      >::value,
      T
  >::type* = nullptr
>
void wrapStringDistanceConsumerAndConfigurable(Wrapper& wrapper)
{
  wrapper
    .def(py::init([](const Settings& settings, const StringDistancePtr& sd) {
      T* result = new T();
      result->setConfiguration(settings);
      result->setStringDistance(sd);
      return result;
    }), R"TOK(
Construct and set the configuration with a Settings object and StringDistance function.
)TOK")
    .def(py::init([](std::map<QString, QString> kvps, const StringDistancePtr& sd) {
      T* result = new T();
      Settings settings;
      for (auto kvp : kvps)
      {
        settings.set(kvp.first, kvp.second);
      }
      result->setConfiguration(settings);
      result->setStringDistance(sd);
      return result;
    }), R"TOK(
Construct and set the configuration with a dict of strings and a StringDistance function.
)TOK")
  ;
}

/**
 * registerSubclass registers and wraps the provided class (T) with a default constructor using
 * parent as the base class.
 */
template<class T, typename Base>
void registerSubclass(py::module_& m, Base& parent)
{
  QString className = T::className().replace("hoot::", "");
  auto result = py::class_<T, std::shared_ptr<T> >
    (m, className.toUtf8().constData(), parent)
    .def(py::init([]() {
      return new T();
    }))
  ;
  wrapAbstractDistanceExtractor<T>(result);
  wrapConfigurable<T>(result);
  wrapConstOsmMapConsumer<T>(result);
  wrapStringDistanceConsumer<T>(result);
  // StringDistanceConsumer and Configurable are implemented, add another constructor
  wrapStringDistanceConsumerAndConfigurable<T>(result);

  PyBindModule::remapNames(result);
}

}

#endif
