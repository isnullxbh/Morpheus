/**
 * @file    DataMember.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

module;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#   include <clang/AST/DeclCXX.h>
#pragma clang diagnostic pop

export module Morpheus.Metadata.DataMember;

export import Std.Strings;

namespace Morpheus::Metadata
{

export class DataMember
{
public:
    auto name() const noexcept -> const std::string&
    {
        return _name;
    }

    static auto extract(const clang::FieldDecl* declaration) -> DataMember
    {
        DataMember instance {};
        instance._name = declaration->getName();
        return instance;
    }

private:
    DataMember() = default;

    std::string _name;
};

} // namespace Morpheus::Metadata