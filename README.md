# Morpheus

An object-relational mapping tool for the C++ programming language

## Prerequisites

- CMake 3.29 or higher
- C++ compiler with `C++23` support (Clang >= 18, GCC >= 14)
- Ninja

**Optional:**

- unixodbc (for generic [ODBC client](Extras/Clients/Odbc))
- libsqlite3 (for [SQLite3 client](Extras/Clients/SQLite))
- libpq (for [PostgreSql client](Extras/Clients/PostgreSql))
- mysqlclient (for [MySQL client](Extras/Clients/MySql))

## Build

To build Morpheus, go to the project's root directory and execute the following
commands:

```shell
cmake -G Ninja -DCMAKE_CXX_FLAGS="-std=c++23" -S . -B build/debug
cmake --build build/debug
```

### Options

| Name                            | Description                                      | Default | Since |
|:--------------------------------|:-------------------------------------------------|:-------:|:-----:|
| MORPHEUS_WITH_POSTGRESQL_CLIENT | Creates a build target for the PostgreSql client |   OFF   | 0.1.0 |
| MORPHEUS_WITH_SQLITE_CLIENT     | Creates a build target for the SQLite3 client    |   OFF   | 0.1.0 |
| MORPHEUS_WITH_ODBC_CLIENT       | Creates a build target for generic ODBC client   |   OFF   | 0.1.0 |
| MORPHEUS_WITH_MYSQL_CLIENT      | Creates a build target for the MySQL client      |   OFF   | 0.1.0 |

## Third-party components

- [FindMySql](Tools/CMake/Modules/FindMySql.cmake) - CMake module to find the MySQL installation  
  Taken from: https://github.com/mysql/mysql-connector-odbc/blob/trunk/cmake/FindMySQL.cmake

## Author

Oleg E. Vorobiov <isnullxbh@gmail.com>

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for more
information.
