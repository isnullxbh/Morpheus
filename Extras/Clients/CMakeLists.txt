if(MORPHEUS_WITH_MYSQL_CLIENT OR MORPHEUS_BUILD_EXAMPLES)
    add_subdirectory(MySql)
endif()

if(MORPHEUS_WITH_ODBC_CLIENT OR MORPHEUS_BUILD_EXAMPLES)
    add_subdirectory(Odbc)
endif()

if(MORPHEUS_WITH_POSTGRESQL_CLIENT OR MORPHEUS_BUILD_EXAMPLES)
    add_subdirectory(PostgreSql)
endif()

if(MORPHEUS_WITH_SQLITE_CLIENT OR MORPHEUS_BUILD_EXAMPLES)
    add_subdirectory(SQLite)
endif()
