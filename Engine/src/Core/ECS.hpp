#pragma once

#include <unordered_map>
#include <vector>
#include <tuple>
#include <type_traits>
#include <cassert>

using Entity = uint32_t;

class Registry {
public:
    Entity createEntity() {
        return nextID++;
    }

    template <typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        auto component = new Component<T>(std::forward<Args>(args)...);
        components_[entity].emplace_back(component);
    }

    template <typename T>
    T* getComponent(Entity entity) const {
        auto it = components_.find(entity);
        if (it != components_.end()) {
            const auto& entityComponents = it->second;
            for (const auto& component : entityComponents) {
                if (component->type() == typeid(T)) {
                    return static_cast<Component<T>*>(component)->data;
                }
            }
        }
        return nullptr;
    }

    ~Registry() {
        for (auto& entityComponents : components_) {
            for (auto component : entityComponents.second) {
                delete component;
            }
        }
    }

private:
    struct ComponentBase {
        virtual ~ComponentBase() = default;
        virtual const std::type_info& type() const = 0;
    };

    template <typename T>
    struct Component : ComponentBase {
        template <typename... Args>
        Component(Args&&... args) : data(new T(std::forward<Args>(args)...)) {}
        T* data;
        const std::type_info& type() const override { return typeid(T); }
    };

private:
    std::unordered_map<Entity, std::vector<ComponentBase*>> components_;
    inline static Entity nextID = 0;
};
