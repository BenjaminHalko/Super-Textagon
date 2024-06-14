#pragma once

#include <engine/comp/_component.h>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <forward_list>
#include <vector>

/*
 * @brief The base class for all entities
 */
class Entity {
    /**
     * @brief Components of the entity
     * @details These components are unique components that may only be added once.
     * The key is the type of the component.
     * The value is a unique pointer to the component.
     * This is a map so that we can easily access the component by its type.
     */
    std::unordered_map<std::type_index, std::unique_ptr<Component>> _components;

    /**
     * @brief The depth of a component
     * @details This is used to order the entities in a set.
     * @note This might be turned into a component in the future.
     */
    int _depth;
public:
    /**
     * @brief Constructs an entity with a list of components
     * @tparam components The components to add to the entity
     * @param depth The depth of the entity
     */
    template <typename... ComponentTypes>
    explicit Entity(ComponentTypes... components, int depth = 0) : _depth(depth) {
        ((_components[typeid(components)] = std::make_unique<ComponentTypes>(std::move(components))), ...);
    }

    /**
     * @brief Gets a component from the entity
     * @tparam ComponentType The type of the component to get
     * @return ComponentType& The component of the entity casted to the correct type
     */
    template <typename ComponentType>
    ComponentType& GetComponent() {
        return *static_cast<ComponentType*>(_components[typeid(ComponentType)].get());
    }

    /**
     * @brief Checks if the entity has a component
     * @tparam ComponentType The type of the component to check
     * @return bool True if the entity has the component
     */
    template <typename... ComponentTypes>
    bool HasComponents() {
        return ((_components.find(typeid(ComponentTypes)) != _components.end()) && ...);
    }

    // Orders the entity inside of sets
    bool operator<(const Entity &other) const;
};