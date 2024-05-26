/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.Sql.ResultSet;

export import Std.Def;

namespace Morpheus::Sql
{

export class ResultSet
{
public:
    virtual ~ResultSet() = default;
    virtual auto size() const noexcept -> std::size_t = 0;
};

} // namespace Morpheus::Sql
