/**
 * @file    Type.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    19.10.2023
 */

#pragma once

namespace Morpheus::Sql
{

/// Defines SQL types.
/// @since 0.1.0
enum class Type
{
    Character,
    CharacterVarying,
    CharacterLargeObject,
    Binary,
    BinaryVarying,
    BinaryLargeObject,
    Numeric,
    Decimal,
    SmallInt,
    Integer,
    BigInt,
    Float,
    Real,
    DoublePrecision,
    Boolean,
    Date,
    Time,
    Timestamp,
    Interval,
    Xml,
    Json
};

} // namespace Morpheus::Sql
