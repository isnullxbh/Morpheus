/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

export module Morpheus.PostgreSql.ResultSet;

export import Morpheus.Sql.ResultSet;

import Std.Utility;
import Morpheus.PostgreSql.Cli;

namespace Morpheus::PostgreSql
{

export class ResultSet
{
public:
    explicit ResultSet(Cli::pg_result* handle) noexcept
        : _handle(handle)
    {}

    ResultSet(const ResultSet&) = delete;

    ResultSet(ResultSet&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~ResultSet()
    {
        if (_handle != nullptr)
        {
            Cli::PQclear(_handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t
    {
        return static_cast<std::size_t>(Cli::PQntuples(_handle));
    }

private:
    Cli::pg_result* _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::PostgreSql
