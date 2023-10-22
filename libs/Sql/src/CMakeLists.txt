add_library(Morpheus.Sql)
add_library(Morpheus::Sql ALIAS Morpheus.Sql)

set_target_properties(Morpheus.Sql
    PROPERTIES
        OUTPUT_NAME "Morpheus.Sql"
        PREFIX      "")

target_include_directories(Morpheus.Sql
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Morpheus.Sql
    PRIVATE
        Morpheus/Sql/Exception.cpp)

target_link_libraries(Morpheus.Sql
    PUBLIC
        Morpheus::Base)
