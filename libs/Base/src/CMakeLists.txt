add_library(Morpheus.Base)
add_library(Morpheus::Base ALIAS Morpheus.Base)

set_target_properties(Morpheus.Base
    PROPERTIES
        OUTPUT_NAME "Morpheus.Base"
        PREFIX      "")

target_include_directories(Morpheus.Base
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Morpheus.Base
    PRIVATE
        Morpheus/Exception.cpp)
