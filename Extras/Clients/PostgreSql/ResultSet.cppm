/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

export module Morpheus.PostgreSql.ResultSet;

import Std.Utility;
export import Morpheus.Sql.ResultSet;
import Morpheus.PostgreSql.Cli;

namespace Morpheus::PostgreSql
{

export class ResultSet : public Sql::ResultSet
{
public:
    explicit ResultSet(Cli::pg_result* handle) noexcept
        : _handle(handle)
    {}

    ResultSet(const ResultSet&) = delete;

    ResultSet(ResultSet&& rhs) noexcept
        : _handle(std::exchange(rhs._handle, nullptr))
    {}

    ~ResultSet() override
    {
        if (_handle != nullptr)
        {
            Cli::PQclear(_handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t override
    {
        return static_cast<std::size_t>(Cli::PQntuples(_handle));
    }

private:
    Cli::pg_result* _handle;
};

} // namespace Morpheus::PostgreSql
