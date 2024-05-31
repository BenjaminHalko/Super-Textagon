#pragma once

#include "../components/_component.hpp"
#include <iostream>
#include <utility>
#include <algorithm>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

class Entity {
    int id;
    bool destroyed = false;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
public:
    Entity() {
        static int next_id = 0;
        id = next_id++;
    }

    template <typename ComponentType, typename... Args>
    void AddComponent(Args&&... args) {
        components[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args)...);
    }

    template <typename ComponentType>
    ComponentType& GetComponent() {
        return *static_cast<ComponentType*>(components[typeid(ComponentType)].get());
    }

    bool getDestroyed() const { return destroyed; }
};