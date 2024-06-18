#pragma once

#include <engine/comp/_component.h>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <string>
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
     * @brief Flags the enemy for deletion
     */
    bool _delete = false;
public:
    /**
     * @brief Constructs an entity with a list of components
     * @tparam components The components to add to the entity
     * @param depth The depth of the entity
     */
    template <typename... ComponentTypes>
    explicit Entity(ComponentTypes&&... components) {
        ((_components[typeid(components)] = std::make_unique<ComponentTypes>(std::forward<ComponentTypes>(components))), ...);
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

    // Flags the entity for deletion
    void Delete();

    // Checks if the entity is flagged for deletion
    [[nodiscard]] bool IsDeleted() const;
};