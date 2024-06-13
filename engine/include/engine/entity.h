#pragma once

#include <engine/comp/_basicComponent.h>
#include <engine/comp/timerComponent.h>
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
    std::unordered_map<std::type_index, std::unique_ptr<BasicComponent>> basicComponents;

    /**
     * @brief Stores all the timers of the entity
     */
    std::vector<std::unique_ptr<TimerComponent>> timers;

    // Tells systems the order in which to execute the entity
    int depth = 0;

    // Tells ECS to destroy the entity
    bool destroyed = false;

protected:
    /**
     * @brief Adds a component to the entity
     * @tparam ComponentType The type of the component to add
     * @tparam Args The arguments to pass to the component constructor
     */
    template <typename ComponentType, typename... Args>
    ComponentType& AddComponent(Args&&... args) {
        basicComponents[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args)...);
        return *static_cast<ComponentType*>(basicComponents[typeid(ComponentType)].get());
    }

    /**
     * @brief Adds a timer to the entity
     * @param script The script to run when the timer ends
     */
    TimerComponent& AddTimer(ScriptComponent script);
public:
    /**
     * @brief Updates the entity each frame
     */
    virtual void Update() {};

    /**
     * @brief Gets a component from the entity
     * @tparam ComponentType The type of the component to get
     * @return ComponentType& The component of the entity casted to the correct type
     */
    template <typename ComponentType>
    ComponentType& GetComponent() {
        return *static_cast<ComponentType*>(basicComponents[typeid(ComponentType)].get());
    }

    /**
     * @brief Checks if the entity has a component
     * @tparam ComponentType The type of the component to check
     * @return bool True if the entity has the component
     */
    template <typename... ComponentTypes>
    bool HasComponents() {
        return ((basicComponents.find(typeid(ComponentTypes)) != basicComponents.end()) && ...);
    }

    /**
     * @brief Gets all the timers of the entity
     */
    std::vector<std::unique_ptr<TimerComponent>>& GetTimers();

    // Orders the entity inside of sets
    bool operator<(const Entity &other) const;

    // Marks the entity for destruction
    void Destroy();

    // Check if the entity is destroyed
    [[nodiscard]] bool gotDestroyed() const;
};