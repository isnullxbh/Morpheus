/**
 * @file    Client.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.Sql.Client;

export import Std.Utility;
export import Morpheus.Base.Uri;
export import Morpheus.Sql.Error;

import Std.Concepts;

namespace Morpheus::Sql
{

export template<typename T>
concept Client = requires(T& client, const Uri& uri)
{
    typename T::Connection;
    { client.connect(uri) } -> std::same_as<std::expected<typename T::Connection, Error>>;
};

} // namespace Morpheus::Sql
