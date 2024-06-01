/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

import Std;
import Morpheus.Mapping;
import Morpheus.Queries;
import Morpheus.SQLite.Client;

using Morpheus::Uri;
using Morpheus::Mapping::Column;
using Morpheus::Mapping::Entity;

struct
[[clang::annotate("Morpheus::Entity", "user")]]
User
{
    [[clang::annotate("Morpheus::Column", "id")]]
    std::size_t id {};

    [[clang::annotate("Morpheus::Column", "name")]]
    std::string name {};
};

template<>
class Entity<User>
{
public:
    static constexpr Column<&User::id>   id   { "id" };
    static constexpr Column<&User::name> name { "name" };

    static constexpr std::string_view table { "\"user\"" };

    template<typename F>
    static constexpr auto for_each(F&& f) -> void
    {
        f(id), f(name);
    }
};

int main()
{
    const auto query =
        Morpheus::QueryBuilder::select(Entity<User>::id, Entity<User>::name)
            .from(Entity<User>::table)
            .build();

    Morpheus::SQLite::Client client {};
    auto try_connect = client.connect(Uri("file:///Users/isnullxbh/testdb"));
    if (!try_connect)
    {
        std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
        return 1;
    }

    auto connection = std::move(try_connect).value();

    auto try_execute = connection.execute(query);
    if (!try_execute)
    {
        std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
        return 1;
    }

    auto result_set = std::move(try_execute).value();
    auto fetcher = result_set.createFetcher();

    while (fetcher.fetch())
    {
        for (std::size_t i = 0; i < 2; ++i)
        {
            std::cout << fetcher.getColumnData(i) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
