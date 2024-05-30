/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.PostgreSql.Connection;

export import Morpheus.Sql.Connection;
export import Morpheus.PostgreSql.ResultSet;

import Std.Utility;
import Morpheus.PostgreSql.Cli;

namespace Morpheus::PostgreSql
{

export class Connection
{
public:
    using ResultSet = PostgreSql::ResultSet;

    explicit Connection(Cli::pg_conn* handle)
        : _handle(handle)
    {}

    Connection(const Connection&) = delete;

    Connection(Connection&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~Connection()
    {
        if (_handle)
        {
            Cli::PQfinish(_handle);
            _handle = nullptr;
        }
    }

    auto operator=(const Connection&) -> Connection& = delete;
    auto operator=(Connection&&) -> Connection& = delete;

    auto execute(std::string_view query) -> std::expected<ResultSet, Sql::Error>
    {
        const auto handle = Cli::PQexec(_handle, query.data());
        const auto status = Cli::PQresultStatus(handle);

        if (status != Cli::ExecStatusType::PGRES_COMMAND_OK &&
            status != Cli::ExecStatusType::PGRES_TUPLES_OK)
        {
            std::string message { Cli::PQresultErrorMessage(handle) };
            Cli::PQclear(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return ResultSet { handle };
    }

private:
    Cli::pg_conn* _handle;
};

static_assert(Sql::Connection<Connection>);

} // namespace Morpheus::PostgreSql
