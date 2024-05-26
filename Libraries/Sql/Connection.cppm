/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.05.2024
 */

export module Morpheus.Sql.Connection;

export import Std.Memory;
export import Std.Strings;
export import Std.Utility;

export import Morpheus.Sql.Error;
export import Morpheus.Sql.ResultSet;

namespace Morpheus::Sql
{

export class Connection
{
public:
    virtual ~Connection() = default;
    virtual auto execute(std::string_view query) -> std::expected<std::shared_ptr<ResultSet>, Error> = 0;
};

} // namespace Morpheus::Sql
