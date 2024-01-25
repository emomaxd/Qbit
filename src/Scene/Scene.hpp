#pragma once

#include <vector>
#include <cstdint>

#include "Components.hpp"

#include <unordered_map>

#include <memory>

#include "../../Dependencies/enTT/src/entt/entt.hpp"

//#include "../Core/ECS.hpp"

struct Rigidbody;

class Scene {
public:

    Scene();

    ~Scene();

    entt::entity createEntity();

    void destroyEntity(entt::entity);

    template <typename T, typename... Args>
    T* addComponent(entt::entity entity, Args&&... args){
        return &registry.emplace<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T* getComponent(entt::entity entity){
        return &registry.get<T>(entity);
    }

    template <typename T>
    void removeComponent(entt::entity entity) {
        registry.remove<T>(entity);
    }
    

    inline uint32_t getSceneID(){return this->sceneID;}

    uint32_t entityCount = 0;

private:
    /// SCENE COUNT
    inline static uint32_t nextID = 0;
    uint32_t sceneID;

    

    std::string name{"Scene - DEFAULT NAME"};

    float TOTAL_TIME{0};
    
    entt::registry registry{};

    std::unordered_map<std::string ,entt::entity* > entityVector;

};