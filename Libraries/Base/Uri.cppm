/**
 * @file    Uri.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    25.05.2024
 */

export module Morpheus.Base.Uri;

export import Std.Strings;

namespace Morpheus
{

export class Uri
{
public:
    explicit Uri(std::string_view str);

    auto str() const noexcept -> const std::string&;

private:
    std::string _str;
};

Uri::Uri(std::string_view str)
    : _str(str)
{}

auto Uri::str() const noexcept -> const std::string&
{
    return _str;
}

} // namespace Morpheus
