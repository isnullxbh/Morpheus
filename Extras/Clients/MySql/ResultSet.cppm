/**
 * @file    ResultSet.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    29.05.2024
 */

export module Morpheus.MySql.ResultSet;

export import Morpheus.Sql.ResultSet;
import Morpheus.MySql.Cli;

namespace Morpheus::MySql
{

export class ResultSet : public Sql::ResultSet
{
public:
    explicit ResultSet(Cli::ResultHandle handle)
        : _handle(handle)
    {}

    ~ResultSet() override
    {
        if (_handle != nullptr)
        {
            Cli::mysql_free_result(_handle);
            _handle = nullptr;
        }
    }

    auto size() const noexcept -> std::size_t override
    {
        return static_cast<std::size_t>(Cli::mysql_num_rows(_handle));
    }

private:
    Cli::ResultHandle _handle;
};

} // namespace Morpheus::MySql
