#pragma once

#include "../components/_component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

/*
 * @brief The base class for all entities
 */
class Entity {
    /**
     * @brief Components of the entity
     * @details The key is the type of the component.
     * The value is a unique pointer to the component.
     * This is a map so that we can easily access the component by its type.
     */
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

    /**
     * @brief Systems that the entity uses
     * @details We can easily check if the entity uses a system by checking if the system type is in this set
     */
    std::unordered_set<std::type_index> systemsToUse;

    // Tells systems the order in which to execute the entity
    int executionPriority = 0;

    // Tells ECS to destroy the entity
    bool destroyed = false;

    /**
     * @brief Adds a component to the entity
     * @tparam ComponentType The type of the component to add
     * @tparam Args The arguments to pass to the component constructor
     */
    template <typename ComponentType, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args)...);
    }
public:
    /**
     * @brief Gets a component from the entity
     * @tparam ComponentType The type of the component to get
     * @return ComponentType& The component of the entity casted to the correct type
     */
    template <typename ComponentType>
    ComponentType& GetComponent() {
        return *static_cast<ComponentType*>(components[typeid(ComponentType)].get());
    }

    bool UsesSystem(std::type_index system) const;

    bool operator<(const Entity &other) const;

    bool gotDestroyed() const;
};