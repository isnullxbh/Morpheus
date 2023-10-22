/**
 * @file    Exception.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    21.10.2023
 */

#pragma once

#include <exception>
#include <format>
#include <string>

namespace Morpheus
{

/// Base class for exceptions defined in the project.
/// @since 0.1.0
class Exception : public std::exception
{
public:
    /// Construct the exception with the specified message.
    /// @tparam Args          Argument types.
    /// @param  format_string Format string.
    /// @param  args          Arguments.
    template<typename... Args>
    explicit Exception(std::format_string<Args...> format_string, Args&&... args);

    explicit Exception(std::string message);

public:
    /// Gets a message that describes the current exception.
    /// @return A reference to the message.
    auto message() const noexcept -> const std::string&;

    /// Gets a message that describes the current exception.
    /// @return A pointer to the message data.
    auto what() const noexcept -> const char*;

private:
    std::string _message; ///< Message.
};

template<typename... Args>
Exception::Exception(std::format_string<Args...> format_string, Args&&... args)
    : _message(std::format(format_string, std::forward<Args>(args)...))
{}

} // namespace Morpheus
