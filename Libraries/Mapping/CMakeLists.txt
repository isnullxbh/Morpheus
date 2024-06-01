add_library(Morpheus.Mapping)

set_target_properties(Morpheus.Mapping
    PROPERTIES
        OUTPUT_NAME "Morpheus.Mapping"
        PREFIX      "")

target_compile_features(Morpheus.Mapping
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Mapping
    PUBLIC
        FILE_SET morpheus_mapping TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Column.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Mapping.cppm)

target_link_libraries(Morpheus.Mapping
    Std)

add_library(Morpheus::Mapping ALIAS Morpheus.Mapping)
