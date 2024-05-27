/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

#include <iostream>

import Morpheus.PostgreSql.Client;
import Morpheus.SQLite.Client;
import Morpheus.Odbc.Client;

auto test(Morpheus::Sql::Client& client, std::string_view connection_str) -> void;

int main()
{
    {
        Morpheus::PostgreSql::Client client {};
        test(client, "postgresql://localhost:5432/testdb");
    }

    {
        Morpheus::SQLite::Client client {};
        test(client, "file:///Users/isnullxbh/testdb");
    }

    {
        auto create_client = Morpheus::Odbc::Client::create();
        if (!create_client)
        {
            std::cerr << "An error occurred: " << create_client.error().message() << std::endl;
        }
        else
        {
            auto client = std::move(create_client).value();
            test(client, "Driver={PostgreSqlOdbc};Database=testdb;Port=5432;");
        }
    }

    return 0;
}

auto test(Morpheus::Sql::Client& client, std::string_view connection_str) -> void
{
    using Morpheus::Uri;

    auto try_connect = client.connect(Uri(connection_str));
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
