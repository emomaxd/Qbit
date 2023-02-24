#include <iostream>
#include <algorithm>

#include "../include/Scene.hpp"

Scene* Scene::_instance = 0;

Scene* Scene::getInstance() 
{
    if (!_instance) {
        _instance = new Scene();
    }
    return _instance;
}

uint64_t Scene::add( std::unique_ptr<Object> o ) 
{
    uint64_t id = nextID;
    
    _objects.push_back(std::move(o));
    
    nextID++;

    return id;
}

bool Scene::remove( const uint64_t& ID )
{
    auto it = std::find_if(_objects.begin(), _objects.end(), [&](const std::unique_ptr<Object>& o){ return o->getID() == ID; });

    if( it != _objects.end() ){
        std::cout << "DELETED\n";
        _objects.erase( it );
        return true;
    }
    std::cout<<"Couldn't remove the box, NOT FOUND!\n";
    return false;
}

void Scene::update( const float &dt ) 
{
    for ( const std::unique_ptr<Object>& o : _objects ) 
    {
        o->update( dt );
    }
    checkCollisions();
}

void Scene::checkCollisions() 
{
   
    for (int i = 0; i < _objects.size(); i++) {
        
        for (int j = i + 1; j < _objects.size(); j++) {
            
            if (_objects[i]->isColliding(_objects[j])) {
                _objects[i]->handleCollision(_objects[j]);
                exit(0);
            }

        }

    }
}

void Scene::listAll(){
    std::cout << "TOTAL OBJECTS : " << _objects.size() << "\n";
    for( const std::unique_ptr<Object>& o : _objects ){
        std::cout << "Object " << o->getID() << " " << o->getPosition();
    }
}

