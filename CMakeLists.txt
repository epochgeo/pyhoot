cmake_minimum_required(VERSION 3.12)
project(hoot)

message(${CMAKE_CURRENT_LIST_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR})

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/conanbuildinfo.cmake)
else()
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Python3 3.8 EXACT COMPONENTS Development)

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
)
message(${CONAN_LIBS})
# We don't need all the conan libraries for linking
target_link_libraries(
    pyhoot
        ${Python3_LIBRARIES}
        ${CONAN_LIBS}
)

