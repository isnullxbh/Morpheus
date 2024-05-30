/**
 * @file    Connection.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    24.05.2024
 */

export module Morpheus.Sql.Connection;

export import Std.Strings;
export import Std.Utility;
export import Morpheus.Sql.Error;

import Std.Concepts;

namespace Morpheus::Sql
{

export template<typename T>
concept Connection = requires(T& connection, std::string_view query)
{
    typename T::ResultSet;
    { connection.execute(query) } -> std::same_as<std::expected<typename T::ResultSet, Error>>;
};

} // namespace Morpheus::Sql
