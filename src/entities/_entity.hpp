#pragma once

#include "../components/_component.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>


class Entity {
    /**
     * @brief Components of the entity
     * @details The key is the type of the component
     * The value is a unique pointer to the component
     * This is a map so that we can easily access the component by its type
     */
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

    /**
     * @brief Systems that the entity uses
     * @details We can easily check if the entity uses a system by checking if the system type is in this set
     */
    std::unordered_set<std::type_index> systemsToUse;

    // Tells ECS the order in which to execute the entity
    int executionPriority = 0;

    // Tells ECS to destroy the entity
    bool destroyed = false;
public:
    /**
     * @brief Adds a component to the entity
     * @tparam ComponentType
     * @tparam Args
     * @details The component is created with the arguments passed
     */
    template <typename ComponentType, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args)...);
    }

    /**
     * @brief Get a component from the entity
     * @details It is casted to the correct type
     * @tparam ComponentType
     * @return ComponentType&
     */
    template <typename ComponentType>
    ComponentType& GetComponent() {
        return *static_cast<ComponentType*>(components[typeid(ComponentType)].get());
    }

    /**
     * @brief Check if the entity uses a system
     * @param systemIndex
     * @return bool
     */
    bool UsesSystem(std::type_index system) const {
        return systemsToUse.find(system) != systemsToUse.end();
    }

    // Orders the entity inside of sets
    bool operator<(const Entity &other) const {
        return executionPriority < other.executionPriority;
    }

    bool gotDestroyed() const { return destroyed; }
    int getExecutionPriority() const { return executionPriority; }
};