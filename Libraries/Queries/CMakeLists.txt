add_library(Morpheus.Queries)

set_target_properties(Morpheus.Queries
    PROPERTIES
        OUTPUT_NAME "Morpheus.Queries"
        PREFIX      "")

target_compile_features(Morpheus.Queries
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Queries
    PUBLIC
        FILE_SET morpheus_queries TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Queries.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/QueryBuilder.cppm)

target_link_libraries(Morpheus.Queries
    Std)

add_library(Morpheus::Queries ALIAS Morpheus.Queries)
