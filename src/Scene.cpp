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

uint64_t Scene::addBox( std::unique_ptr<Box> box ) 
{
    uint64_t id = nextID;
    
    _boxes.push_back(std::move(box));
    
    nextID++;

    return id;
}

bool Scene::removeBox( const uint64_t& ID )
{
    auto it = std::find_if(_boxes.begin(), _boxes.end(), [&](const std::unique_ptr<Box>& b){ return b->ID == ID; });

    if( it != _boxes.end() ){
        std::cout << "DELETED\n";
        _boxes.erase( it );
        return true;
    }
    std::cout<<"Couldn't remove the box, NOT FOUND!\n";
    return false;
}

void Scene::update( const float &dt ) 
{
    // NEED 2 SEPERATE THREADS , PARALLEL 
    for ( const std::unique_ptr<Box>& box : _boxes ) 
    {
        box->update( dt );
    }
    checkCollisions();
}

void Scene::checkCollisions() 
{
   
    for (int i = 0; i < _boxes.size(); i++) {
        
        for (int j = i + 1; j < _boxes.size(); j++) {
            
            if (_boxes[i]->isColliding(_boxes[j])) {
                _boxes[i]->handleCollision(_boxes[j]);
                exit(0);
            }

        }

    }
}

void Scene::listAllBoxes(){
    std::cout << "TOTAL BOXES : " << _boxes.size() << "\n";
    for( const std::unique_ptr<Box>& b : _boxes ){
        std::cout << "Box " << b->ID << " " << b->getPos();
    }
}

