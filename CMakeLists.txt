cmake_minimum_required(VERSION 3.12)
project(hoot)

add_definitions("-std=c++11")

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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libcode.version")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Python3 3.6 EXACT COMPONENTS Development)

list(REMOVE_ITEM CONAN_LIBS
    wayland-server wayland-cursor wayland-egl wayland-client 
    Qt5Gui
    X11 X11-xcb xcb fontenc ICE SM Xau Xaw7 Xt Xcomposite Xcursor Xdamage Xfixes Xdmcp Xext Xft Xi Xinerama xkbfile Xmu Xmuu Xpm Xrandr Xrender XRes Xss Xtst Xv XvMC Xxf86vm xcb-xkb xcb-icccm xcb-image xcb-shm xcb-keysyms xcb-randr xcb-render xcb-render-util xcb-shape xcb-sync xcb-xfixes xcb-xinerama xcb-util xcb-dri3
)

set(CONAN_LIBS HootCore)

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
    ${CONAN_INCLUDE_DIRS}
    ${CONAN_INCLUDE_DIRS_HOOTENANNY}
)

target_link_libraries(
    pyhoot
    ${Python3_LIBRARIES}
    ${CONAN_LIBS}
    ${CONAN_LIBS_HOOTENANNY}
)

