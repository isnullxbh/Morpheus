/**
 * @file    Entity.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    02.06.2024
 */

export module Morpheus.Metadata.Entity;

namespace Morpheus::Metadata
{

export enum class EntityKind
{
    Class,
};

export template<typename T>
struct EntityTraits;

export class Entity
{
public:
    virtual ~Entity() = default;
    virtual auto kind() const noexcept -> EntityKind = 0;
};

} // namespace Morpheus::Metadata
