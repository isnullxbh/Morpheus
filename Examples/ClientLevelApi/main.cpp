/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

#include <iostream>

import Morpheus.PostgreSql.Client;
import Morpheus.SQLite.Client;
import Morpheus.Odbc.Client;

void postgreSql();
void sqlite();
void odbc();

int main()
{
    postgreSql();
    sqlite();
    odbc();
    return 0;
}

void postgreSql()
{
    using namespace Morpheus::PostgreSql;
    using Morpheus::Uri;

    Client client {};
    auto try_connect = client.connect(Uri("postgresql://localhost:5432/testdb"));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return;
    }

    auto connection = std::move(try_connect).value();

    auto try_execute = connection->execute("SELECT * FROM user");
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return;
    }

    auto result_set = std::move(try_execute).value();
    std::cout << "Result set size: " << result_set->size() << std::endl;
}

void sqlite()
{
    using namespace Morpheus::SQLite;
    using Morpheus::Uri;

    Client client {};
    auto try_connect = client.connect(Uri("file:///Users/isnullxbh/testdb"));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return;
    }

    auto connection = std::move(try_connect).value();

    auto try_execute = connection->execute("SELECT * FROM user");
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return;
    }

    auto result_set = std::move(try_execute).value();
    std::cout << "Result set size: " << result_set->size() << std::endl;
}

void odbc()
{
    using namespace Morpheus::Odbc;
    using Morpheus::Uri;

    auto create_client = Client::create();
    if (!create_client)
    {
        std::cerr << "An error occurred: " << create_client.error().message() << std::endl;
        return;
    }

    auto client = std::move(create_client).value();

    auto try_connect = client.connect(Uri("Driver={PostgreSqlOdbc};Database=testdb;Port=5432;"));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return;
    }

    auto connection = std::move(try_connect).value();

    auto try_execute = connection->execute("SELECT * FROM user");
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return;
    }

    auto result_set = std::move(try_execute).value();
    std::cout << "Result set size: " << result_set->size() << std::endl;
}
