cmake_minimum_required(VERSION 3.12)
project(hoot)

message(${CMAKE_CURRENT_LIST_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions("-std=c++11")

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
else()
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Boost)
find_package(Python3 3.6 EXACT COMPONENTS Development)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_library(
    HootCore_LIBRARIES
    HootCore
    REQUIRED
    HINTS $ENV{HOOT_HOME}/lib
)

find_library(
    node_LIBRARIES
    node
    REQUIRED
)

#find_library(
#    HootJs_LIBRARIES
#    HootJs
#    REQUIRED
#    HINTS $ENV{HOOT_HOME}/lib
#)

set(PYHOOT_HOME ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE PYHOOT_FILES CONFIGURE_DEPENDS 
    ${PYHOOT_HOME}/src/*.h
    ${PYHOOT_HOME}/src/*.cpp
)

add_library(pyhoot ${PYHOOT_FILES})
target_include_directories(
    pyhoot
    PRIVATE 
        ${Python3_INCLUDE_DIRS}
        $ENV{HOOT_HOME}/hoot-core/src/main/cpp
        ${Boost_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
)

target_link_libraries(
    pyhoot
    ${CONAN_LIBS}
    ${Python3_LIBRARIES}
	${HootCore_LIBRARIES}
#    ${HootJs_LIBRARIES}
    ${node_LIBRARIES}
)

