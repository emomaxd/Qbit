#pragma once

#include <vector>
#include <cstdint>

#include "Box.hpp"

class Scene {
private:
    static Scene* _instance;
    std::vector< Box* > _boxes;
    uint64_t nextID = 0 ;
    Scene() {}

public:
    static Scene* getInstance();

    uint64_t addBox( Box* box );

    void removeBox( const Box& box );

    void removeBox( const uint64_t& ID );
    
    void update( const float &dt );

    void listAllBoxes();

    void checkCollisions();
};
