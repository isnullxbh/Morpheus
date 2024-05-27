/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    27.05.2024
 */

export module Morpheus.Odbc.ResultSet;

import Morpheus.Sql.ResultSet;
import Morpheus.Odbc.Cli;

namespace Morpheus::Odbc
{

export class ResultSet : public Sql::ResultSet
{
public:
    explicit ResultSet(Cli::Handle handle)
        : _handle(handle)
    {}

    ~ResultSet() override
    {
        if (_handle != nullptr)
        {
            Cli::SQLFreeHandle(Cli::HandleType::Statement, _handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t override
    {
        // TODO
        return 0;
    }

private:
    Cli::Handle _handle;
};

} // namespace Morpheus::Odbc
