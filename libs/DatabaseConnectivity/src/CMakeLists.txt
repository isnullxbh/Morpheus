add_library(Morpheus.DatabaseConnectivity)
add_library(Morpheus::DatabaseConnectivity ALIAS Morpheus.DatabaseConnectivity)

set_target_properties(Morpheus.DatabaseConnectivity
    PROPERTIES
        OUTPUT_NAME "Morpheus.DatabaseConnectivity"
        PREFIX      "")

target_include_directories(Morpheus.DatabaseConnectivity
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Morpheus.DatabaseConnectivity
    PRIVATE
        Morpheus/DatabaseConnectivity/DatabaseConnectivity.cpp)

target_link_libraries(Morpheus.DatabaseConnectivity
    PUBLIC
        Morpheus::Sql)
