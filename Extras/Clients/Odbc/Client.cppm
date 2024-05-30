/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.Client;

export import Morpheus.Sql.Client;
export import Morpheus.Odbc.Connection;

import Morpheus.Odbc.Cli;
import Morpheus.Odbc.Diagnostic;

namespace Morpheus::Odbc
{

export class Client
{
public:
    using Connection = Odbc::Connection;

    Client(Client&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~Client()
    {
        if (_handle != nullptr)
        {
            Cli::SQLFreeHandle(Cli::HandleType::Environment, _handle);
            _handle = nullptr;
        }
    }

    auto connect(const Uri& uri) -> std::expected<Connection, Sql::Error>
    {
        Cli::Handle handle {};

        auto ec = Cli::SQLAllocHandle(Cli::HandleType::Connection, _handle, &handle);
        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Connection, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        ec = Cli::SQLDriverConnect(handle, nullptr, (Cli::Char*)uri.str().data(), Cli::nts, nullptr, 0, nullptr, 0);
        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Connection, handle);
            Cli::SQLFreeHandle(Cli::HandleType::Connection, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        return Connection { handle };
    }

    static auto create() noexcept -> std::expected<Client, Sql::Error>
    {
        Cli::Handle handle {};

        auto ec = Cli::SQLAllocHandle(Cli::HandleType::Environment, Cli::null_handle, &handle);
        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Environment, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        ec = Cli::SQLSetEnvAttr(handle, Cli::EnvironmentAttribute::OdbcVersion,
            reinterpret_cast<Cli::Pointer>(Cli::Version::v3), -1);

        if (ec != Cli::StatusCode::Ok && ec != Cli::StatusCode::OkWithInfo)
        {
            auto diagnostic = Diagnostic::retrieve(Cli::HandleType::Environment, handle);
            Cli::SQLFreeHandle(Cli::HandleType::Environment, handle);
            return std::unexpected { std::move(diagnostic).toError() };
        }

        return Client { handle };
    }

private:
    explicit Client(Cli::Handle handle)
        : _handle(handle)
    {}

    Cli::Handle _handle;
};

static_assert(Sql::Client<Client>);

} // namespace Morpheus::Odbc
