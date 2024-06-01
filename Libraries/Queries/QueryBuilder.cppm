/**
 * @file    QueryBuilder.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

export module Morpheus.Queries.QueryBuilder;
export import Std.Strings;

import Std.Utility;

namespace Morpheus
{

export class SelectStatement
{
public:
    template<typename... Columns>
    explicit SelectStatement(Columns&&... columns)
    {
        static_assert(sizeof...(Columns) > 0, "Columns are not specified");
        _query += "SELECT ";
        ((_query += columns, _query += ", "), ...);
        const auto length = _query.length();
        _query = std::move(_query).substr(0, length - 2);
    }

    auto from(std::string_view table) -> SelectStatement&
    {
        _query += " FROM ";
        _query += table;
        return *this;
    }

    auto build() -> std::string
    {
        return std::exchange(_query, "");
    }

private:
    std::string _query {};
};


export class QueryBuilder
{
public:
    template<typename... Columns>
    static auto select(Columns&&... columns) -> SelectStatement
    {
        return SelectStatement { std::forward<Columns>(columns)... };
    }
};

} // namespace Morpheus
