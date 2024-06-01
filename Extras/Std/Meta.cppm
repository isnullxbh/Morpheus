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
using ::std::remove_cv_t;
using ::std::remove_cvref_t;
using ::std::is_same_v;
using ::std::true_type;
using ::std::false_type;

} // namespace std
