/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    28.05.2024
 */

export module Morpheus.MySql.Client;

export import Morpheus.Sql.Client;
import Morpheus.MySql.Cli;
import Morpheus.MySql.Connection;

namespace Morpheus::MySql
{

export class Client : public Sql::Client
{
public:
    auto connect(const Uri& uri) -> std::expected<std::shared_ptr<Sql::Connection>, Sql::Error> override
    {
        const auto handle = Cli::mysql_init(nullptr);

        if (!handle)
        {
            return std::unexpected<Sql::Error> { "Handle is null" };
        }

        // TODO: get params from URI
        if (!Cli::mysql_real_connect(handle, "192.168.1.54", "dbuser", "dbpass", "testdb", 3306, nullptr, 0))
        {
            std::string message { Cli::mysql_error(handle) };
            Cli::mysql_close(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return std::make_shared<Connection>(handle);
    }
};

} // namespace Morpheus::MySql
