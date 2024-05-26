include(FindPostgreSQL)

add_library(Morpheus.Clients.PostgreSql)

set_target_properties(Morpheus.Clients.PostgreSql
    PROPERTIES
        OUTPUT_NAME "Morpheus.Clients.PostgreSql"
        PREFIX      "")

target_compile_features(Morpheus.Clients.PostgreSql
    PUBLIC
        cxx_std_20)

target_include_directories(Morpheus.Clients.PostgreSql
    PRIVATE
        ${PostgreSQL_INCLUDE_DIRS})

target_sources(Morpheus.Clients.PostgreSql
    PUBLIC
        FILE_SET morpheus_clients_postgresql TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Client.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/PostgreSql.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Pq.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/ResultSet.cppm)

target_link_directories(Morpheus.Clients.PostgreSql
    PRIVATE
        ${PostgreSQL_LIBRARY_DIRS})

target_link_libraries(Morpheus.Clients.PostgreSql
    ${PostgreSQL_LIBRARIES}
    Morpheus::Sql)

add_library(Morpheus::Clients::PostgreSql ALIAS Morpheus.Clients.PostgreSql)
