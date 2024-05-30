/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

export module Morpheus.SQLite.Connection;

export import Morpheus.Sql.Connection;
export import Morpheus.SQLite.ResultSet;
import Std.Utility;
import Morpheus.SQLite.Cli;

namespace Morpheus::SQLite
{

export class Connection : public Sql::Connection
{
public:
    explicit Connection(Cli::sqlite3* handle)
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
            Cli::sqlite3_close(_handle);
            _handle = nullptr;
        }
    }

    auto execute(std::string_view query) -> std::expected<std::shared_ptr<Sql::ResultSet>, Sql::Error> override
    {
        Cli::sqlite3_stmt* handle {};

        const auto ec =
            Cli::sqlite3_prepare(_handle, query.data(), static_cast<int>(query.size()), &handle, nullptr);

        if (ec != Cli::StatusCode::Ok)
        {
            std::string message { Cli::sqlite3_errmsg(_handle) };
            Cli::sqlite3_finalize(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return std::make_shared<ResultSet>(handle);
    }

private:
    Cli::sqlite3* _handle;
};

} // namespace Morpheus::SQLite
