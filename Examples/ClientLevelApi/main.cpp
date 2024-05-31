/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

#include <iostream>
#include <type_traits>

import Morpheus.PostgreSql.Client;
import Morpheus.SQLite.Client;
import Morpheus.Odbc.Client;
import Morpheus.MySql;

auto test(Morpheus::Sql::Client auto& client, std::string_view connection_str) -> void;

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

    {
        Morpheus::MySql::Client client {};
        test(client, "mysql://192.168.1.54:3306/testdb");
    }

    return 0;
}

auto test(Morpheus::Sql::Client auto& client, std::string_view connection_str) -> void
{
    using Morpheus::Uri;

    auto try_connect = client.connect(Uri(connection_str));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return;
    }

    auto connection = std::move(try_connect).value();

    constexpr std::string query =
        std::is_same_v<Morpheus::MySql::Client, std::remove_cvref_t<decltype(client)>>
            ? "SELECT * FROM user"
            : "SELECT * FROM \"user\"";

    auto try_execute = connection.execute(query);
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return;
    }

    auto result_set = std::move(try_execute).value();
    std::cout << "Result set size: " << result_set.size() << std::endl;

    auto fetcher = result_set.createFetcher();
    while (fetcher.fetch())
    {
        for (std::size_t i = 0; i < 4; ++i)
        {
            std::cout << fetcher.getColumnData(i) << ' ';
        }
        std::cout << std::endl;
    }
}
