/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

#include <filesystem>

#include "User.hpp"

import Std;
import Morpheus.Mapping;
import Morpheus.Queries;
import Morpheus.SQLite.Client;
import Morpheus.Metadata.Class;
import Morpheus.Metadata.Extractor;

using Morpheus::Uri;
using Morpheus::Mapping::Column;
using Morpheus::Mapping::Entity;

template<>
class Entity<App::User>
{
public:
    static constexpr Column<&App::User::id>   id   { "id" };
    static constexpr Column<&App::User::name> name { "name" };

    static constexpr std::string_view table { "\"user\"" };

    template<typename F>
    static constexpr auto for_each(F&& f) -> void
    {
        f(id), f(name);
    }
};

int main()
{
    const std::filesystem::path example_directory { EXAMPLE_DIR };

    Morpheus::Metadata::Extractor extractor;
    const auto registry = extractor.extract(example_directory / "User.hpp", {});

    registry.forEach<Morpheus::Metadata::Class>([](const Morpheus::Metadata::Class& entity)
    {
        std::cout << "Class: " << entity.qualifiedName() << std::endl;
        for (const auto& member : entity.dataMembers())
        {
            std::cout << "  - member: " << member.name() << "\n";
        }
        std::cout << std::endl;
    });

    // const auto query =
    //     Morpheus::QueryBuilder::select(Entity<App::User>::id, Entity<App::User>::name)
    //         .from(Entity<App::User>::table)
    //         .build();
    //
    // Morpheus::SQLite::Client client {};
    // auto try_connect = client.connect(Uri("file:///Users/isnullxbh/testdb"));
    // if (!try_connect)
    // {
    //     std::cerr << "An error occurred: " << try_connect.error().message() << std::endl;
    //     return 1;
    // }
    //
    // auto connection = std::move(try_connect).value();
    //
    // auto try_execute = connection.execute(query);
    // if (!try_execute)
    // {
    //     std::cerr << "An error occurred: " << try_execute.error().message() << std::endl;
    //     return 1;
    // }
    //
    // auto result_set = std::move(try_execute).value();
    // auto fetcher = result_set.createFetcher();
    //
    // while (fetcher.fetch())
    // {
    //     for (std::size_t i = 0; i < 2; ++i)
    //     {
    //         std::cout << fetcher.getColumnData(i) << ' ';
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}
