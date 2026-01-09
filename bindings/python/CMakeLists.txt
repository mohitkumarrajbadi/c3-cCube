cmake_minimum_required(VERSION 3.18)
project(c3_python LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use modern Python discovery (important with conda)
set(PYBIND11_FINDPYTHON ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

add_library(c3 MODULE
    c3_pybind.cpp
    ../../core/context/context.cpp
    ../../core/store/store.cpp
    ../../core/recall/recall.cpp
    ../../core/update/update.cpp
    ../../core/prune/prune.cpp
    ../../core/memory/memory.cpp
)

target_include_directories(c3 PRIVATE ../../core)

target_link_libraries(c3 PRIVATE pybind11::module Python3::Python)

set_target_properties(c3 PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)
