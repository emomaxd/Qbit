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

    Object* getObject(uint64_t ID);

    void listAll();

    void checkCollisions();

    void printObject(Object* o, float dt);

    void printObject(uint64_t ID, float dt);

private:

    static float TOTAL_TIME;
    static Scene* _instance;
    std::vector< std::unique_ptr<Object> > _objects;
    uint64_t nextID = 0 ;
    Scene() {}

};
