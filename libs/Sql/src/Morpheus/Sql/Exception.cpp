/**
 * @file    Exception.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    21.10.2023
 */

#include <Morpheus/Sql/Exception.hpp>

namespace Morpheus::Sql
{

Exception::Exception(std::string message)
    : Morpheus::Exception(std::move(message))
{}

Exception::Exception(std::string message, std::string state)
    : Morpheus::Exception(std::move(message))
    , _state(std::move(state))
{}

Exception::Exception(std::string message, std::string state, int code)
    : Morpheus::Exception(std::move(message))
    , _state(std::move(state))
    , _code(code)
{}

auto Exception::state() const noexcept -> const std::string&
{
    return _state;
}

auto Exception::code() const noexcept -> int
{
    return _code;
}

} // namespace Morpheus::Sql
