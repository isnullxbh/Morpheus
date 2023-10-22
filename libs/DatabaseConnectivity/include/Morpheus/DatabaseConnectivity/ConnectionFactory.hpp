/**
 * @file    ConnectionFactory.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    18.10.2023
 */

#pragma once

#include <string_view>

#include <Morpheus/DatabaseConnectivity/Connection.hpp>

namespace Morpheus::DatabaseConnectivity
{

/// A database connection factory.
/// @since 0.1.0
class ConnectionFactory
{
public:
    /// Destructor.
    virtual ~ConnectionFactory() = default;

    /// Checks if the factory able to create a connection with the specified URI.
    /// @param  uri Connection URI.
    /// @return If the factory can create a connection - true, otherwise - false.
    virtual auto supports(std::string_view uri) const noexcept -> bool = 0;

    /// Creates a connection to a database according to the specified connection URI.
    /// @param  uri Connection URI.
    /// @return A pointer to the created connection.
    /// @throws Sql::Exception Will be thrown if a database error occurs.
    virtual auto createConnection(std::string_view uri) -> Connection::Ptr = 0;
};

} // namespace Morpheus::DatabaseConnectivity
