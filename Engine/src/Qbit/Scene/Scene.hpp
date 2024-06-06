#pragma once

#include <vector>
#include <cstdint>

#include "Components.hpp"

#include <unordered_map>

#include <memory>

#include <entt.hpp>

//#include "../Core/ECS.hpp"

struct Rigidbody;

class Scene {
public:

    Scene();

    ~Scene();

    entt::entity CreateEntity();

    void DestroyEntity(entt::entity);

    template <typename T, typename... Args>
    T* AddComponent(entt::entity entity, Args&&... args){
        return &m_Registry.emplace<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T* GetComponent(entt::entity entity){
        return &m_Registry.get<T>(entity);
    }

    template <typename T>
    void RemoveComponent(entt::entity entity) {
        m_Registry.remove<T>(entity);
    }

    void DeleteAllEntities() {
        // If there are no entities, nothing to delete
        if (m_EntityCount == 0)
            return;

        // Keep the reference to the main camera entity at index 0
        entt::entity mainCamera = m_EntityVector[0]; // Assuming Entity is your entity type

        // Clear the vector and map
        m_EntityVector.clear();
        m_EntityMap.clear();

        // Add the main camera entity back to the vector
        m_EntityVector.push_back(mainCamera);

        m_EntityMap.insert({ GetComponent<EntityProperties>(mainCamera)->name = std::string("Main Camera"), &mainCamera });

        // Update the entity count
        m_EntityCount = 1;
    }

    inline uint32_t GetSceneID(){ return m_SceneID; }

    inline std::string GetName(){ return m_Name; }

    entt::entity FindEntity(const std::string& name);

    std::vector<entt::entity> m_EntityVector;


    entt::registry m_Registry{};

    uint32_t m_EntityCount = 0;

private:
    /// SCENE COUNT
    inline static uint32_t nextID = 0;
    uint32_t m_SceneID;

    


    std::string m_Name{"Scene - DEFAULT NAME"};    

    std::unordered_map<std::string ,entt::entity* > m_EntityMap;

};