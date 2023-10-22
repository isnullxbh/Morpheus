/**
 * @file    Exception.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    21.10.2023
 */

#include <Morpheus/Exception.hpp>

namespace Morpheus
{

Exception::Exception(std::string message)
    : _message(std::move(message))
{}

auto Exception::message() const noexcept -> const std::string&
{
    return _message;
}

auto Exception::what() const noexcept -> const char*
{
    return _message.data();
}

} // namespace Morpheus
