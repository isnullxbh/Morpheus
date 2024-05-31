/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    29.05.2024
 */

export module Morpheus.MySql.ResultSet;

export import Morpheus.Sql.ResultSet;

import Std.Utility;
import Morpheus.MySql.Cli;

namespace Morpheus::MySql
{

export class Fetcher
{
public:
    explicit Fetcher(Cli::ResultHandle handle)
        : _handle(handle)
    {}

    auto fetch() -> bool
    {
        if (!_record)
        {
            return false;
        }

        _record = Cli::mysql_fetch_row(_handle);

        return _record != nullptr;
    }

    auto getColumnData(std::size_t index) const -> const char*
    {
        return _record[index];
    }

private:
    Cli::ResultHandle _handle;
    Cli::Record       _record;
};

export class ResultSet
{
public:
    explicit ResultSet(Cli::ResultHandle handle)
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
            Cli::mysql_free_result(_handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t
    {
        return static_cast<std::size_t>(Cli::mysql_num_rows(_handle));
    }

    auto createFetcher() const noexcept -> Fetcher
    {
        return Fetcher { _handle };
    }

private:
    Cli::ResultHandle _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::MySql
