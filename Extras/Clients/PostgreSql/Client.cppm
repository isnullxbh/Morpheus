/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

export module Morpheus.PostgreSql.Client;

export import Morpheus.Sql.Client;
export import Morpheus.PostgreSql.Connection;

import Morpheus.PostgreSql.Cli;

namespace Morpheus::PostgreSql
{

export class Client
{
public:
    using Connection = PostgreSql::Connection;

    auto connect(const Uri& uri) -> std::expected<Connection, Sql::Error>
    {
        auto* const handle = Cli::PQconnectdb(uri.str().data());

        if (Cli::PQstatus(handle) != Cli::ConnStatusType::CONNECTION_OK)
        {
            std::string message { Cli::PQerrorMessage(handle) };
            Cli::PQfinish(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return Connection { handle };
    }
};

static_assert(Sql::Client<Client>);

} // namespace Morpheus::PostgreSql
