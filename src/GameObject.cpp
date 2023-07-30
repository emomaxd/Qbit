#include "../include/GameObject.hpp"

#include <algorithm>

uint32_t GameObject::nextID = 0;

GameObject::GameObject(){
    id = nextID++;
}

GameObject::~GameObject(){

    std::for_each(components.begin(), components.end(), [](auto& pair) {
            std::vector<Component*>& componentVector = pair.second;
            for (Component* component : componentVector) {
                delete component;
            }
        });

        components.clear();

    
}

