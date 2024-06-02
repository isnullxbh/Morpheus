/**
 * @file    Class.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

module;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#   include <clang/AST/DeclCXX.h>
#pragma clang diagnostic pop

export module Morpheus.Metadata.Class;

export import Std.Strings;
export import Std.Vector;
export import Std.Memory;
export import Morpheus.Metadata.DataMember;
export import Morpheus.Metadata.Entity;

namespace Morpheus::Metadata
{

export class Class : public Entity
{
public:
    using DataMembers = std::vector<DataMember>;

    auto kind() const noexcept -> EntityKind override
    {
        return EntityKind::Class;
    }

    auto qualifiedName() const noexcept -> const std::string&
    {
        return _qualified_name;
    }

    auto dataMembers() const noexcept -> const DataMembers&
    {
        return _data_members;
    }

    static auto extract(const clang::CXXRecordDecl* declaration) -> std::unique_ptr<Class>
    {
        std::unique_ptr<Class> instance { new Class() };

        instance->_qualified_name = declaration->getQualifiedNameAsString();

        for (auto it = declaration->field_begin(); it != declaration->field_end(); ++it)
        {
            instance->_data_members.push_back(DataMember::extract(*it));
        }

        return instance;
    }

private:
    Class() = default;

    std::string _qualified_name;
    DataMembers _data_members;
};

template<>
struct EntityTraits<Class>
{
    static constexpr EntityKind kind { EntityKind::Class };
};

} // namespace Morpheus::Metadata
