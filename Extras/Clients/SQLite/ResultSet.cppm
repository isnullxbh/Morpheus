/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

export module Morpheus.SQLite.ResultSet;

export import Std.Strings;
export import Morpheus.Sql.ResultSet;

import Std.Utility;
import Morpheus.SQLite.Cli;

namespace Morpheus::SQLite
{

export class Fetcher
{
public:
    explicit Fetcher(Cli::StatementHandle handle)
        : _handle(handle)
    {}

    auto fetch() -> bool
    {
        if (_done)
        {
            return false;
        }

        const auto ec = Cli::sqlite3_step(_handle);
        _done = (ec == Cli::StatusCode::Done);
        return ec == Cli::StatusCode::Row;
    }

    auto getColumnData(std::size_t index) const -> const char*
    {
        return reinterpret_cast<const char*>(Cli::sqlite3_column_text(_handle, static_cast<int>(index)));
    }

private:
    Cli::StatementHandle _handle;
    bool                 _done;
};

export class ResultSet
{
public:
    explicit ResultSet(Cli::sqlite3_stmt* handle)
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
            Cli::sqlite3_finalize(_handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t
    {
        // TODO: it's very (!) bad solution
        std::size_t count {};
        while (Cli::sqlite3_step(_handle) == Cli::StatusCode::Row)
        {
            ++count;
        }
        Cli::sqlite3_reset(_handle);
        return count;
    }

    auto createFetcher() const -> Fetcher
    {
        return Fetcher { _handle };
    }

private:
    Cli::sqlite3_stmt* _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::SQLite
