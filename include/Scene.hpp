#pragma once

#include <unordered_map>
#include <cstdint>

#include "Box.hpp"

class Scene {
private:
    static Scene* _instance;
    std::unordered_map< uint64_t, Box* > _boxes; // USE SHARED POINTER HERE
    uint64_t nextID = 0 ;
    Scene() {}

public:
    static Scene* getInstance();

    uint64_t addBox( Box* box );

    void removeBox( uint64_t ID );

    void update( const float &dt );

    void checkCollisions();
};
