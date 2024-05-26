/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

#include <expected>

export module Morpheus.Sql.Client;

export import Std.Memory;
export import Std.Utility;

export import Morpheus.Base.Uri;
export import Morpheus.Sql.Connection;
export import Morpheus.Sql.Error;

namespace Morpheus::Sql
{

export class Client
{
public:
    virtual ~Client() = default;
    virtual auto connect(const Uri& uri) -> std::expected<std::shared_ptr<Connection>, Error> = 0;
};

} // namespace Morpheus::Sql
