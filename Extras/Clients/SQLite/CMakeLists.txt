include(FindSQLite3)

add_library(Morpheus.Clients.SQLite)

set_target_properties(Morpheus.Clients.SQLite
    PROPERTIES
        OUTPUT_NAME "Morpheus.Clients.SQLite"
        PREFIX      "")

target_compile_features(Morpheus.Clients.SQLite
    PUBLIC
        cxx_std_20)

target_include_directories(Morpheus.Clients.SQLite
    PRIVATE
        ${SQLite3_INCLUDE_DIRS})

target_sources(Morpheus.Clients.SQLite
    PUBLIC
        FILE_SET morpheus_clients_sqlite TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Cli.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Client.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/ResultSet.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/SQLite.cppm)

target_link_libraries(Morpheus.Clients.SQLite
    ${SQLite3_LIBRARIES}
    Morpheus::Sql)

add_library(Morpheus::Clients::SQLite ALIAS Morpheus.Clients.SQLite)
