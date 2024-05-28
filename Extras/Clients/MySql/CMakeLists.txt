include(${PROJECT_SOURCE_DIR}/Tools/CMake/Modules/FindMySql.cmake)

add_library(Morpheus.Clients.MySql)

set_target_properties(Morpheus.Clients.MySql
    PROPERTIES
        OUTPUT_NAME "Morpheus.Clients.MySql"
        PREFIX      "")

target_compile_features(Morpheus.Clients.MySql
    PUBLIC
        cxx_std_20)

target_include_directories(Morpheus.Clients.MySql
    PRIVATE
        ${MYSQL_INCLUDE_DIR})

target_sources(Morpheus.Clients.MySql
    PUBLIC
        FILE_SET morpheus_clients_mysql TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Cli.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Client.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/MySql.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/ResultSet.cppm)

target_link_directories(Morpheus.Clients.MySql
    PRIVATE
        ${MYSQL_LIB_DIR})

target_link_libraries(Morpheus.Clients.MySql
    ${MYSQL_LIBRARIES}
    Morpheus::Sql)

add_library(Morpheus::Clients::MySql ALIAS Morpheus.Clients.MySql)
