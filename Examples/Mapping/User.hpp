/**
 * @file    User.hpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

#pragma once

#include <string>

namespace App
{

struct
[[clang::annotate("Morpheus::Entity", "user")]]
User
{
    [[clang::annotate("Morpheus::Column", "id")]]
    std::size_t id {};

    [[clang::annotate("Morpheus::Column", "name")]]
    std::string name {};
};

} // namespace App
