#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "Object.hpp"

class Scene {
public:

    static Scene* getInstance();

    uint64_t add( std::unique_ptr<Object> o );

    bool remove( const uint64_t& ID );
    
    void update( const float &dt );

    void listAll();

    void checkCollisions();

private:

    static Scene* _instance;
    std::vector< std::unique_ptr<Object> > _objects;
    uint64_t nextID = 0 ;
    Scene() {}

};
