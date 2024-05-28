add_executable(Morpheus.Examples.ClientLevelApi)

set_target_properties(Morpheus.Examples.ClientLevelApi
    PROPERTIES
        OUTPUT_NAME "ClientLevelApi"
        PREFIX      "")

target_compile_features(Morpheus.Examples.ClientLevelApi
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Examples.ClientLevelApi
    PRIVATE
        main.cpp)

target_link_libraries(Morpheus.Examples.ClientLevelApi
    Morpheus::Clients::PostgreSql
    Morpheus::Clients::SQLite
    Morpheus::Clients::Odbc
    Morpheus::Clients::MySql)
