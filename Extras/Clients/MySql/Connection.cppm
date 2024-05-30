/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    28.05.2024
 */

export module Morpheus.MySql.Connection;

export import Morpheus.Sql.Connection;

import Std.Utility;
import Morpheus.MySql.Cli;
import Morpheus.MySql.ResultSet;

namespace Morpheus::MySql
{

export class Connection : public Sql::Connection
{
public:
    explicit Connection(Cli::Handle handle) noexcept
        : _handle(handle)
    {}

    Connection(const Connection&) = delete;

    Connection(Connection&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~Connection() override
    {
        if (_handle != nullptr)
        {
            Cli::mysql_close(_handle);
            _handle = nullptr;
        }
    }

    auto execute(std::string_view query) -> std::expected<std::shared_ptr<Sql::ResultSet>, Sql::Error> override
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

        return std::make_shared<ResultSet>(handle);
    }

private:
    Cli::Handle _handle;
};

} // namespace Morpheus::MySql
