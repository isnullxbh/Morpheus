add_library(Morpheus.Sql)

set_target_properties(Morpheus.Sql
    PROPERTIES
        OUTPUT_NAME "Morpheus.Sql"
        PREFIX      "")

target_compile_features(Morpheus.Sql
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Sql
    PUBLIC
        FILE_SET morpheus_sql TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Client.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Error.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/ResultSet.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Sql.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/State.cppm)

target_link_libraries(Morpheus.Sql
    Std
    Morpheus::Base)

add_library(Morpheus::Sql ALIAS Morpheus.Sql)
