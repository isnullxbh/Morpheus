/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.ResultSet;

export import Morpheus.Sql.ResultSet;

import Std.Utility;
import Morpheus.Odbc.Cli;

namespace Morpheus::Odbc
{

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

private:
    Cli::Handle _handle;
};

static_assert(Sql::ResultSet<ResultSet>);

} // namespace Morpheus::Odbc
