/**
 * @file    Statement.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    18.10.2023
 */

#pragma once

#include <memory>
#include <string_view>

#include <Morpheus/DatabaseConnectivity/Result.hpp>

namespace Morpheus::DatabaseConnectivity
{

/// An entity that used to execute regular SQL statement.
/// @since 0.1.0
class Statement
{
public:
    using Ptr = std::unique_ptr<Statement>; ///< A type of pointer to statement.

public:
    /// Destructor.
    virtual ~Statement() = default;

    /// Executes the specified SQL query.
    /// @param  query SQL query.
    /// @return A pointer to the created result.
    /// @throws Sql::Exception Will be thrown if a database error occurs or this method is called on the closed
    ///         statement.
    virtual auto execute(std::string_view query) -> Result::Ptr = 0;

    /// Close the current statement.
    /// @throws Sql::Exception Will be throw if a database error occurs.
    virtual auto close() -> void = 0;
};

} // namespace Morpheus::DatabaseConnectivity
