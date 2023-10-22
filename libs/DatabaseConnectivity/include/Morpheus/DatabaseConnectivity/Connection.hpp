/**
 * @file    Connection.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    18.10.2023
 */

#pragma once

#include <memory>

#include <Morpheus/DatabaseConnectivity/Statement.hpp>

namespace Morpheus::DatabaseConnectivity
{

/// A database connection.
/// @since 0.1.0
class Connection
{
public:
    using Ptr = std::unique_ptr<Connection>; ///< Type of a pointer to the connection.

public:
    /// Destructor.
    virtual ~Connection() = default;

    /// Creates statement.
    /// @return A pointer to the created statement.
    /// @throws Sql::Exception Will be thrown if a database error occurs or this method is called on the closed
    ///         connection.
    virtual auto createStatement() -> Statement::Ptr = 0;

    /// Close the connection.
    /// @throws Sql::Exception Will be thrown if a database error occurs.
    virtual auto close() -> void = 0;
};

} // namespace Morpheus::DatabaseConnectivity
