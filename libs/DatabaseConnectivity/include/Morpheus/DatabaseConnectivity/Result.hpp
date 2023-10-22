/**
 * @file    Result.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    18.10.2023
 */

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <Morpheus/Sql/Type.hpp>

namespace Morpheus::DatabaseConnectivity
{

/// A result of query execution.
/// @since 0.1.0
class Result
{
public:
    using Ptr = std::unique_ptr<Result>; ///< A type of pointer to result.

public:
    /// A result metadata.
    class Metadata
    {
    public:
        /// Contains information about column in a result.
        struct Column
        {
            std::string name;     ///< Name.
            Sql::Type   type;     ///< Type.
            bool        nullable; ///< Indicates that column may be null.
        };

    public:
        /// Destructor.
        virtual ~Metadata() = default;

        /// Gets a number of columns in result.
        /// @return Number of columns.
        virtual auto columnCount() const noexcept -> std::size_t = 0;

        /// Gets info about columns in the result.
        /// @return A reference to collection of the column info items.
        virtual auto columns() const noexcept -> const std::vector<Column>& = 0;
    };

public:
    /// Destructor.
    virtual ~Result() = default;

    /// Gets result's metadata.
    /// @return A reference to metadata.
    virtual auto metadata() const noexcept -> const Metadata& = 0;

    /// Fetches the next row from result.
    /// @return If record has been fetched - true, otherwise - false.
    /// @throws Sql::Exception Will be thrown if a database error occurs or this method is called on the closed result.
    virtual auto fetch() -> bool = 0;

    /// Retrieves the value of the specified column in the current row.
    /// @param  index Column index.
    /// @return A pointer to data.
    /// @throws Sql::Exception Will be thrown if a database error occurs or this method is called on the closed result.
    virtual auto getColumnData(std::size_t index) -> std::string_view = 0;

    /// Checks if value of the specified column is null.
    /// @param  index Column index.
    /// @return If column value is null - true, otherwise - false.
    /// @throws Sql::Exception Will be thrown if a database error occurs or this method is called on the closed result.
    virtual auto isNull(std::size_t index) -> bool = 0;

    /// Close the result.
    /// @throws Sql::Exception Will be thrown if a database error occurs.
    virtual auto close() -> void = 0;
};

} // namespace Morpheus::DatabaseConnectivity
