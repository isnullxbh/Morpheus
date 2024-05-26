/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

export module Morpheus.PostgreSql.Client;

export import Morpheus.Base.Uri;
import Morpheus.Sql.Client;

export import Morpheus.PostgreSql.Connection;
import Morpheus.PostgreSql.Pq;

namespace Morpheus::PostgreSql
{

export class Client : public Sql::Client
{
public:
    auto connect(const Uri& uri) -> std::expected<std::shared_ptr<Sql::Connection>, Sql::Error> override
    {
        auto* const handle = Pq::PQconnectdb(uri.str().data());

        if (Pq::PQstatus(handle) != Pq::ConnStatusType::CONNECTION_OK)
        {
            std::string message { Pq::PQerrorMessage(handle) };
            Pq::PQfinish(handle);
            return std::unexpected<Sql::Error> { std::move(message) };
        }

        return std::make_shared<Connection>(handle);
    }
};

} // namespace Morpheus::PostgreSql
