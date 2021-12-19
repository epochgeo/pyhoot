/**
 * MIT License
 * https://opensource.org/licenses/MIT
 * 
 * @copyright Copyright (C) 2021 EpochGeo LLC (http://www.epochgeo.com/)
 */

#ifndef __PYHOOT_STABLE_H__
#define __PYHOOT_STABLE_H__

// Order _shouldn't_ matter here but if we include pybind11 after HootCoreStable we get a compiler
// error.
// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// hoot
#include <hoot/core/HootConfig.h>
#include <hoot/core/HootCoreStable.h>
#include <hoot/js/HootJsStable.h>

#endif
