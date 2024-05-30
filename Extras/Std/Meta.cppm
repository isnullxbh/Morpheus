/**
 * @file    Meta.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    26.05.2024
 */

module;

#include <type_traits>

export module Std.Meta;

export namespace std
{

using ::std::underlying_type_t;
using ::std::remove_reference_t;
using ::std::remove_cvref_t;

} // namespace std
