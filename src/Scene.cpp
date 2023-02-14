#include "../include/Scene.hpp"
#include <iostream>

Scene *Scene::_instance = 0;

Scene *Scene::getInstance() 
{
    if (!_instance) {
        _instance = new Scene();
    }
    return _instance;
}

uint64_t Scene::addBox( Box* box ) 
{
    uint64_t id = nextID;
    
    _boxes[id] = box ;
    
    nextID++;

    return id;
}

void Scene::removeBox( uint64_t ID )
{
    auto it = _boxes.find(ID);

    if( it != _boxes.end() )
        _boxes.erase(it);
}

void Scene::update( const float &dt ) 
{
    for ( auto box : _boxes ) 
    {
        box.second->update( dt );
    }
    checkCollisions();
}

void Scene::checkCollisions() 
{
    for (int i = 0; i < _boxes.size(); i++) {
        
        for (int j = i + 1; j < _boxes.size(); j++) {

            if (_boxes[i]->isColliding(*_boxes[j])) {
                _boxes[i]->handleCollision(*_boxes[j]);
            }

        }

    }
}
