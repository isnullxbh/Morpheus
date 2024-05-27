include(FindODBC)

add_library(Morpheus.Clients.Odbc)

set_target_properties(Morpheus.Clients.Odbc
    PROPERTIES
        OUTPUT_NAME "Morpheus.Clients.Odbc"
        PREFIX      "")

target_compile_features(Morpheus.Clients.Odbc
    PUBLIC
        cxx_std_20)

target_include_directories(Morpheus.Clients.Odbc
    PRIVATE
        ${ODBC_INCLUDE_DIRS})

target_sources(Morpheus.Clients.Odbc
    PUBLIC
        FILE_SET morpheus_clients_odbc TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Cli.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Client.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Odbc.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/ResultSet.cppm)

target_link_libraries(Morpheus.Clients.Odbc
    ${ODBC_LIBRARIES}
    Morpheus::Sql)

add_library(Morpheus::Clients::Odbc ALIAS Morpheus.Clients.Odbc)
