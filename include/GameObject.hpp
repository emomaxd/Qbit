#pragma once

#include "Object.hpp"
#include "Scene.hpp"
#include "Component.hpp"

#include <unordered_map>
#include <typeindex>


// Inherits from Object - NEW OBJECT CLASS IN PROGRESS
class GameObject {
public:

    GameObject();
    ~GameObject();

    template <typename T>
    void AddComponent(){
        T* component = new T();
    
        component->gameObject = this;

        auto typeIndex = std::type_index(typeid(T));

        auto it = components.find(typeIndex);
        if (it == components.end()) {
            components.emplace(typeIndex, std::vector<Component*>());
            it = components.find(typeIndex);
        }

        it->second.push_back(static_cast<Component*>(component));
    }
        
    /// same type multiple component - not for every component
    /// transform and rb not allowed but collider allowed
    
    template <typename T>
    T* GetComponent(){
        auto typeIndex = std::type_index(typeid(T));
        auto it = components.find(typeIndex);
        if (it != components.end() && !it->second.empty()) {
            return static_cast<T*>(it->second.front());
        }
        return nullptr;
    }

    template <typename T>
    std::vector<Component*>* GetComponents(){
        auto typeIndex = std::type_index(typeid(T));
        auto it = components.find(typeIndex);
        if (it != components.end()) {
            return &it->second;
        }
        return nullptr;
    }

    // Properties
    bool activeInHierarchy;
    const bool activeSelf{true};
    Scene* scene;
    std::string tag;
    uint32_t id;
    static uint32_t nextID; 

private:
    std::unordered_map<std::type_index, std::vector<Component*>> components;

};