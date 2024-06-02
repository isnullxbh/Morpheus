/**
 * @file    EntityRegistry.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    02.06.2024
 */

export module Morpheus.Metadata.EntityRegistry;

import Std.Maps;
import Std.Memory;
import Std.Meta;
import Std.Utility;
import Std.Vector;
import Morpheus.Metadata.Entity;

namespace Morpheus::Metadata
{

export class EntityRegistry
{
public:
    EntityRegistry() = default;
    EntityRegistry(const EntityRegistry&) = delete;
    EntityRegistry(EntityRegistry&&) = default;

    auto add(std::unique_ptr<Entity> entity) -> void
    {
        _entities[entity->kind()].push_back(std::move(entity));
    }

    template<typename ConcreteEntity, typename F>
    auto forEach(F&& f) const -> void
    {
        constexpr auto kind = EntityTraits<ConcreteEntity>::kind;
        if (_entities.contains(kind))
        {
            for (const auto& entity : _entities.at(kind))
            {
                f(*static_cast<const ConcreteEntity*>(entity.get()));
            }
        }
    }

private:
    std::unordered_map<EntityKind, std::vector<std::unique_ptr<Entity>>> _entities {};
};

} // namespace Morpheus::Metadata
