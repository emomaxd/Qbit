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
    

    inline uint32_t GetSceneID(){ return m_SceneID; }

    inline std::string GetName(){ return m_Name; }

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