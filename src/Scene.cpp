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

uint64_t Scene::addBox( Box* box ) 
{
    uint64_t id = nextID;
    
    _boxes.push_back(box);
    
    nextID++;

    return id;
}
/*
void Scene::removeBox( const Box& box )
{
    auto it = std::find_if(_boxes.begin(), _boxes.end(), [](const Box* b,const Box& box){ return b->ID == box.ID; });

    if( it != _boxes.end() ){
        _boxes.erase( it );
        return;
    }
    std::cout<<"Couldn't remove the box, NOT FOUND!\n";
}

void Scene::removeBox( const uint64_t& ID )
{
    auto it = std::find_if(_boxes.begin(), _boxes.end(), [](const Box* b,const uint64_t& ID){ return b->ID == ID; });

    if( it != _boxes.end() ){
        _boxes.erase( it );
        return;
    }
    std::cout<<"Couldn't remove the box, NOT FOUND!\n";
}
*/
void Scene::update( const float &dt ) 
{
    for ( auto box : _boxes ) 
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
            }

        }

    }
}
/*
void Scene::listAllBoxes(){
    for( auto b : _boxes ){
        std::cout << "Box " << b->ID << " " << b->_pos;
    }
}
*/
