/**
 * @file    Memory.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

module;

#include <memory>

export module Std.Memory;

export namespace std
{

using ::std::unique_ptr;
using ::std::shared_ptr;
using ::std::make_unique;
using ::std::make_shared;

} // namespace std
