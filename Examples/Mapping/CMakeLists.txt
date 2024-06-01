add_executable(Morpheus.Examples.Mapping)

set_target_properties(Morpheus.Examples.Mapping
    PROPERTIES
        OUTPUT_NAME "Mapping"
        PREFIX      "")

target_compile_features(Morpheus.Examples.Mapping
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Examples.Mapping
    PRIVATE
        main.cpp)

target_link_libraries(Morpheus.Examples.Mapping
    Morpheus::Mapping
    Morpheus::Queries
    Morpheus::Clients::SQLite)
