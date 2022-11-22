cmake_minimum_required(VERSION 3.12)
project(hoot)

add_definitions("-std=c++11")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(${CMAKE_CURRENT_BINARY_DIR})
message(${CMAKE_CURRENT_LIST_DIR})

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
else()
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
endif()

conan_basic_setup()

# Only export the PyInit_* method
# Taken from https://anadoxin.org/blog/control-over-symbol-exports-in-gcc.html/
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libcode.version")

# Only show the first 5 errors.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=5")
add_compile_definitions(HOOT_HAVE_NODE_NODE_H)

# This library isn't used directly
list(FILTER CONAN_LIBS EXCLUDE REGEX "^icu.*")

list(APPEND CONAN_LIBS libicui18n.a libicuuc.a)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Python3 3.7...<3.8 COMPONENTS Development)

list(REMOVE_ITEM CONAN_LIBS
    wayland-server wayland-cursor wayland-egl wayland-client 
    Qt5Gui
    X11 X11-xcb xcb fontenc ICE SM Xau Xaw7 Xt Xcomposite Xcursor Xdamage
    Xfixes Xdmcp Xext Xft Xi Xinerama xkbfile Xmu Xmuu Xpm Xrandr Xrender XRes
    Xss Xtst Xv XvMC Xxf86vm xcb-xkb xcb-icccm xcb-image xcb-shm xcb-keysyms
    xcb-randr xcb-render xcb-render-util xcb-shape xcb-sync xcb-xfixes
    xcb-xinerama xcb-util xcb-dri3
)
list(APPEND CONAN_LIBS libqsqlite.a)
link_directories({$CONAN_QT_ROOT}/bin/archdatadir/plugins/sqldrivers/)

set(PYHOOT_HOME ${CMAKE_CURRENT_LIST_DIR})

include_directories(BEFORE ${PYHOOT_HOME}/src/)

file(GLOB_RECURSE PYHOOT_FILES CONFIGURE_DEPENDS 
    ${PYHOOT_HOME}/src/*.h
    ${PYHOOT_HOME}/src/*.cpp
)

add_library(pyhoot ${PYHOOT_FILES})
target_include_directories(
    pyhoot
    PRIVATE 
    ${Python3_INCLUDE_DIRS}
    ${CONAN_INCLUDE_DIRS}
    ${CONAN_INCLUDE_DIRS_HOOTENANNY}
)

target_link_libraries(
    pyhoot
    HootJs
    HootTest
    HootCore
    ${Python3_LIBRARIES}
    ${CONAN_LIBS}
)
target_precompile_headers(
    pyhoot
    PUBLIC ${PYHOOT_HOME}/src/hoot/py/PyHootStable.h
)

file(COPY ${CONAN_HOOTENANNY_ROOT}/conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/rules DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/docs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/gdal DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/proj.db DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_HOOTENANNY_ROOT}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_ICU_ROOT}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CONAN_QT_ROOT}/bin/archdatadir/plugins/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/)

