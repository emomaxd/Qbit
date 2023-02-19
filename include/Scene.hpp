#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "Box.hpp"

class Scene {
private:

    static Scene* _instance;
    std::vector< std::unique_ptr<Box> > _boxes;
    uint64_t nextID = 0 ;
    Scene() {}

public:

    static Scene* getInstance();

    uint64_t addBox( std::unique_ptr<Box> box );

    bool removeBox( const uint64_t& ID );
    
    void update( const float &dt );

    void listAllBoxes();

    void checkCollisions();
};
