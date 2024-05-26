/**
 * @file    State.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

#include <cstdint>

export module Morpheus.Sql.State;

namespace Morpheus::Sql
{

export enum class State : std::uint64_t
{};

} // namespace Morpheus::Sql
