add_executable(Morpheus.Examples.Mapping)

set_target_properties(Morpheus.Examples.Mapping
    PROPERTIES
        OUTPUT_NAME "Mapping"
        PREFIX      "")

target_compile_features(Morpheus.Examples.Mapping
    PUBLIC
        cxx_std_20)

target_compile_definitions(Morpheus.Examples.Mapping
    PRIVATE
        EXAMPLE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_sources(Morpheus.Examples.Mapping
    PRIVATE
        User.hpp
        main.cpp)

target_link_libraries(Morpheus.Examples.Mapping
    Morpheus::Mapping
    Morpheus::Metadata
    Morpheus::Queries
    Morpheus::Clients::SQLite)
