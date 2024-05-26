/**
 * @file    Error.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.Sql.Error;

export import Std.Strings;
export import Std.Utility;

export import Morpheus.Sql.State;

namespace Morpheus::Sql
{

export class Error
{
public:
    explicit Error(std::string message) noexcept;

    auto message() const noexcept -> const std::string&;

private:
    std::string _message;
    State       _state       {};
    int         _vendor_code {};
};

Error::Error(std::string message) noexcept
    : _message(std::move(message))
{}

auto Error::message() const noexcept -> const std::string&
{
    return _message;
}

} // namespace Morpheus::Sql
