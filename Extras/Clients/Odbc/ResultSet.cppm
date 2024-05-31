/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.ResultSet;

export import Morpheus.Sql.ResultSet;

import Std.Utility;
import Std.Meta;
import Morpheus.Odbc.Cli;

namespace Morpheus::Odbc
{

export class Fetcher
{
public:
    explicit Fetcher(Cli::Handle handle)
        : _handle(handle)
    {}

    auto fetch() -> bool
    {
        if (_done)
        {
            return false;
        }

        const auto ec = Cli::SQLFetch(_handle);
        _done = (ec == Cli::StatusCode::NoData);
        return ec == Cli::StatusCode::Ok || ec == Cli::StatusCode::OkWithInfo;
    }

    auto getColumnData(std::size_t index) -> const char*
    {
        Cli::SQLGetData(_handle,
            static_cast<Cli::USmallInt>(index + 1),
            static_cast<std::underlying_type_t<Cli::DataType>>(Cli::DataType::Char),
            &_buffer[0],
            1024,
            nullptr);

        return &_buffer[0];
    }

private:
    Cli::Handle _handle;
    bool        _done {};
    char        _buffer[1024];
};

export class ResultSet
{
public:
    explicit ResultSet(Cli::Handle handle)
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
            Cli::SQLFreeHandle(Cli::HandleType::Statement, _handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t
    {
        // TODO
        return 0;
    }

    auto createFetcher() -> Fetcher
    {
        return Fetcher { _handle };
    }

private:
    Cli::Handle _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::Odbc
