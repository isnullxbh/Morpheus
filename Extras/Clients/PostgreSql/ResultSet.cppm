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

export class Fetcher
{
public:
    explicit Fetcher(Cli::ResultHandle handle)
        : _handle(handle)
        , _size(static_cast<std::size_t>(Cli::PQntuples(_handle)))
    {}

    auto fetch() -> bool
    {
        if ((_record_index + 1) == _size)
        {
            return false;
        }

        ++_record_index;
        return true;
    }

    auto getColumnData(std::size_t index) const -> const char*
    {
        return Cli::PQgetvalue(_handle, static_cast<int>(_record_index), static_cast<int>(index));
    }

private:
    Cli::ResultHandle _handle;
    std::size_t       _record_index { static_cast<std::size_t>(-1) };
    std::size_t       _size;
};


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

    auto createFetcher() const noexcept -> Fetcher
    {
        return Fetcher { _handle };
    }

private:
    Cli::pg_result* _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::PostgreSql
