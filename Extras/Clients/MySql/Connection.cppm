/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    28.05.2024
 */

export module Morpheus.MySql.Connection;

export import Morpheus.Sql.Connection;
export import Morpheus.MySql.ResultSet;

import Std.Utility;
import Morpheus.MySql.Cli;

namespace Morpheus::MySql
{

export class Connection
{
public:
    using ResultSet = MySql::ResultSet;

    explicit Connection(Cli::Handle handle) noexcept
        : _handle(handle)
    {}

    Connection(const Connection&) = delete;

    Connection(Connection&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~Connection()
    {
        if (_handle != nullptr)
        {
            Cli::mysql_close(_handle);
            _handle = nullptr;
        }
    }

    auto execute(std::string_view query) -> std::expected<ResultSet, Sql::Error>
    {
        if (Cli::mysql_query(_handle, query.data()))
        {
            return std::unexpected<Sql::Error> { Cli::mysql_error(_handle) };
        }

        const auto handle = Cli::mysql_store_result(_handle);

        if (!handle)
        {
            return std::unexpected<Sql::Error> { Cli::mysql_error(_handle) };
        }

        return ResultSet { handle };
    }

private:
    Cli::Handle _handle;
};

static_assert(Sql::Connection<Connection>);

} // namespace Morpheus::MySql
