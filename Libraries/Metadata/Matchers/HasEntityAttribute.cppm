/**
 * @file    HasEntityAttribute.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    02.06.2024
 */

module;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#   include <clang/ASTMatchers/ASTMatchers.h>
#pragma clang diagnostic pop

export module Morpheus.Metadata.HasEntityAttribute;

namespace Morpheus::Metadata
{

export class HasEntityAttribute
    : public clang::ast_matchers::internal::MatcherInterface<clang::Decl>
{
public:
    bool matches(const clang::Decl& declaration,
        [[maybe_unused]] clang::ast_matchers::internal::ASTMatchFinder* finder,
        [[maybe_unused]] clang::ast_matchers::internal::BoundNodesTreeBuilder* builder) const override
    {
        auto found { false };
        for (const auto* attribute : declaration.attrs())
        {
            if (attribute->getKind() == clang::attr::Annotate)
            {
                const auto* annotate_attribute = static_cast<const clang::AnnotateAttr*>(attribute);
                if (annotate_attribute->getAnnotation() == "Morpheus::Entity")
                {
                    found = true;
                    break;
                }
            }
        }
        return found;
    }
};

export auto hasEntityAttribute() -> clang::ast_matchers::internal::Matcher<clang::Decl>
{
    return clang::ast_matchers::internal::makeMatcher(new HasEntityAttribute());
}

} // namespace Morpheus::Metadata
