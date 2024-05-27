/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

export module Morpheus.SQLite.Client;

import Std.Meta;

export import Morpheus.Sql.Client;
import Morpheus.SQLite.Cli;
export import Morpheus.SQLite.Connection;

namespace Morpheus::SQLite
{

export class Client : public Sql::Client
{
public:
    auto connect(const Uri& uri) -> std::expected<std::shared_ptr<Sql::Connection>, Sql::Error> override
    {
        Cli::sqlite3* handle {};

        std::underlying_type_t<Cli::Flags> flags {};
        flags |= Cli::Flags::Uri;
        flags |= Cli::Flags::ReadWrite;
        flags |= Cli::Flags::Create;

        if (Cli::sqlite3_open_v2(uri.str().data(), &handle, flags, nullptr) != Cli::StatusCode::Ok)
        {
            std::string message { Cli::sqlite3_errmsg(handle) };
            Cli::sqlite3_close(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return std::make_shared<Connection>(handle);
    }
};

} // namespace Morpheus::SQLite
