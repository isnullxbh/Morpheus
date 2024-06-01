/**
 * @file    StringStream.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

module;

#include <sstream>

export module Std.StringStream;

export namespace std
{

using ::std::stringstream;
using ::std::ostringstream;
using ::std::operator <<;

} // namespace std
