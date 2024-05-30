/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.Connection;

export import Morpheus.Sql.Connection;
export import Morpheus.Odbc.ResultSet;

import Std.Utility;
import Morpheus.Odbc.Cli;
import Morpheus.Odbc.Diagnostic;

namespace Morpheus::Odbc
{

export class Connection
{
public:
    using ResultSet = Odbc::ResultSet;

    explicit Connection(Cli::Handle handle)
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
            Cli::SQLDisconnect(_handle);
            Cli::SQLFreeHandle(Cli::HandleType::Connection, _handle);
            _handle = nullptr;
        }
    }

    auto execute(std::string_view query) -> std::expected<ResultSet, Sql::Error>
    {
        Cli::Handle handle {};

        auto ec = Cli::SQLAllocHandle(Cli::HandleType::Statement, _handle, &handle);
        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Statement, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        ec = Cli::SQLExecDirect(handle, (Cli::Char*)query.data(), query.size());
        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Statement, handle);
            Cli::SQLFreeHandle(Cli::HandleType::Statement, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        return ResultSet { handle };
    }

private:
    Cli::Handle _handle;
};

static_assert(Sql::Connection<Connection>);

} // namespace Morpheus::Odbc
