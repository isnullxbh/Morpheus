/**
 * @file    Column.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

export module Morpheus.Mapping.Column;

export import Std.Strings;
import Std.Meta;

namespace Morpheus::Mapping
{

export template<auto Ptr>
class Column
{
public:
    constexpr explicit Column(std::string_view name)
        : _name(name)
    {}

    constexpr auto name() const noexcept -> std::string_view
    {
        return _name;
    }

    static constexpr auto ptr = Ptr;

    constexpr operator std::string_view() const noexcept
    {
        return _name;
    }

private:
    std::string_view _name;
};

namespace Detail
{

template<typename T>
struct IsColumn : std::false_type {};

template<auto Ptr>
struct IsColumn<Column<Ptr>> : std::true_type {};

} // namespace Detail

export template<typename T>
struct IsColumn : Detail::IsColumn<std::remove_cv_t<T>>
{};

} // namespace Morpheus::Mapping
