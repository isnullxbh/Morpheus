/**
 * @file    Exception.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    21.10.2023
 */

#pragma once

#include <string>

#include <Morpheus/Exception.hpp>

namespace Morpheus::Sql
{

/// Base class for exceptions associated with database interaction.
/// @since 0.1.0
class Exception : public Morpheus::Exception
{
public:
    /// Construct the exception with the specified message.
    /// @param message Message.
    explicit Exception(std::string message);

    /// Construct the exception with the specified message and SQL state.
    /// @tparam message Message.
    /// @param  state   SQL state.
    explicit Exception(std::string message, std::string state);

    /// Construct the exception with the specified message, SQL state and vendor specific error code.
    /// @tparam message Message.
    /// @param  state   SQL state.
    /// @param  code    Error code.
    explicit Exception(std::string message, std::string state, int code);

public:
    /// Gets the SQL state for the error represented by the current exception.
    /// @return A reference to string that contains SQL state.
    auto state() const noexcept -> const std::string&;

    /// Gets the vendor-specific code for error represented by the current exception.
    /// @return Error code.
    auto code() const noexcept -> int;

public:
    std::string _state { "<none>" }; ///< SQL state.
    int         _code  { 0 };        ///< Error code.
};

} // namespace Morpheus::Sql
