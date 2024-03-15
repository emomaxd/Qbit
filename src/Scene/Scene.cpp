#include <iostream>
#include <algorithm>
#include <string>

#include "Scene.hpp"

Scene::Scene(){
    m_EntityVector.reserve(1000);
    m_SceneID = nextID++;
    
    m_Name = std::string("Scene" + std::to_string(m_SceneID));
}

Scene::~Scene(){
    
    std::cout << m_Name + " DESTRUCTED\n";    
}

entt::entity Scene::CreateEntity(){
    auto entity = m_Registry.create();

    std::string name = "GameObject" + std::to_string(m_EntityCount++);

    Transform transform; /// (0, 0, 0)

    EntityProperties entityProperties{false, name}; // isActive = false, name = name, std::vector = null

    AddComponent<Transform>(entity, transform);
    AddComponent<EntityProperties>(entity, entityProperties);

    m_EntityMap.insert( std::make_pair(name, &entity));
    m_EntityVector.push_back(entity);

    return entity;
}

void Scene::DestroyEntity(entt::entity entity)
{
   m_Registry.destroy(entity);
}