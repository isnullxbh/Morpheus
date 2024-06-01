/**
 * @file    IO.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

module;

#include <iostream>

export module Std.IO;

export namespace std
{

using ::std::cout;
using ::std::clog;
using ::std::cerr;
using ::std::cin;
using ::std::endl;
using ::std::operator<<;

} // namespace std
