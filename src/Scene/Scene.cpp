#include <iostream>
#include <algorithm>
#include <string>

#include "Scene.hpp"

Scene::Scene() : TOTAL_TIME(0) {
    entityVector.reserve(1000);
    sceneID = nextID++;
    
    name = std::string("Scene - " + std::to_string(sceneID));
}

Scene::~Scene(){
    
    std::cout << name + " DESTRUCTED\n";    
}

entt::entity Scene::createEntity(){
    auto entity = registry.create();
    entityVector.insert( std::make_pair("GameObject " + entityCount++, &entity));
    return entity;
}

void Scene::destroyEntity(entt::entity entity)
{
   registry.destroy(entity);
}