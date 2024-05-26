/**
 * @file    Utility.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

#include <expected>
#include <utility>

export module Std.Utility;

export namespace std
{

using ::std::expected;
using ::std::unexpected;
using ::std::move;
using ::std::forward;

} // namespace std
