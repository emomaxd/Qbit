#pragma once

#include "Object.hpp"
#include "Scene.hpp"
#include "Transform.hpp"


#include <string>
#include <unordered_map>

// Inherits from Object - NEW OBJECT CLASS IN PROGRESS
class GameObject {
public:

    void AddComponent(Component c);

    template <typename T>
    T* AddComponent() {
        T* component = new T();
        component->entity = this;
        components[typeid(T).name()] = component;
        return component;
    }

    template <typename T>
    T* GetComponent() {
        return static_cast<T*>(components[typeid(T).name()]);
    }

    // Properties
    Transform transform;
    bool activeInHierarchy;
    const bool activeSelf;
    Scene* scene;
    std::string tag;

private:
    std::unordered_map<std::string, Component*> components;

};