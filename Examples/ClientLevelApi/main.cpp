/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

#include <iostream>

import Morpheus.PostgreSql.Client;

int main()
{
    using namespace Morpheus::PostgreSql;
    using Morpheus::Uri;

    Client client {};
    auto try_connect = client.connect(Uri("postgresql://localhost:5432/testdb"));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return EXIT_FAILURE;
    }

    auto connection = std::move(try_connect).value();

    auto try_execute = connection->execute("SELECT * FROM user");
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return EXIT_FAILURE;
    }

    auto result_set = std::move(try_execute).value();
    std::cout << "Result set size: " << result_set->size() << std::endl;

    return 0;
}
