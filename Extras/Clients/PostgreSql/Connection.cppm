/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.PostgreSql.Connection;

import Morpheus.Sql.Connection;

import Std.Utility;
import Morpheus.PostgreSql.Pq;
export import Morpheus.PostgreSql.ResultSet;

namespace Morpheus::PostgreSql
{

export class Connection : public Sql::Connection
{
public:
    explicit Connection(Pq::pg_conn* handle)
        : _handle(handle)
    {}

    Connection(const Connection&) = delete;

    Connection(Connection&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~Connection() override
    {
        if (_handle)
        {
            Pq::PQfinish(_handle);
            _handle = nullptr;
        }
    }

    auto operator=(const Connection&) -> Connection& = delete;
    auto operator=(Connection&&) -> Connection& = delete;

    auto execute(std::string_view query) -> std::expected<std::shared_ptr<Sql::ResultSet>, Sql::Error> override
    {
        const auto handle = Pq::PQexec(_handle, query.data());
        const auto status = Pq::PQresultStatus(handle);

        if (status != Pq::ExecStatusType::PGRES_COMMAND_OK &&
            status != Pq::ExecStatusType::PGRES_TUPLES_OK)
        {
            std::string message { Pq::PQresultErrorMessage(handle) };
            Pq::PQclear(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return std::make_shared<ResultSet>(handle);
    }

private:
    Pq::pg_conn* _handle;
};

} // namespace Morpheus::PostgreSql
