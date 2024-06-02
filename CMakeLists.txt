cmake_minimum_required(VERSION 3.29)
project(Morpheus VERSION 0.0.0
                 DESCRIPTION "An object-relational mapping tool for the C++ programming language"
                 HOMEPAGE_URL "https://github.com/isnullxbh/Morpheus"
                 LANGUAGES C CXX)

include(Tools/CMake/Options.cmake)

message(STATUS
    "CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES=${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}")

add_subdirectory(Libraries)
add_subdirectory(Extras)
add_subdirectory(Examples)
