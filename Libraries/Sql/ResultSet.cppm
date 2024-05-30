/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.Sql.ResultSet;

export import Std.Def;
import Std.Concepts;

namespace Morpheus::Sql
{

export template<typename T>
concept ResultSet = requires(T& set)
{
    { set.size() } -> std::same_as<std::size_t>;
};

} // namespace Morpheus::Sql
