#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "Object.hpp"


class Scene {
public:

    Scene() : TOTAL_TIME(0) {sceneID = nextID++;}

    void add( std::unique_ptr<Object> o );

    bool remove( const uint64_t& ID );
    
    void update( const float &dt );

    Object* getObject(uint64_t ID);

    void listAll();

    void checkCollisions();

    void printObject(Object* o);

    void printObject(uint64_t ID);

    int objectCount();

    const std::vector<std::unique_ptr<Object>>& getObjects() const;

    uint32_t getSceneID(){return this->sceneID;}

private:
    /// SCENE COUNT
    static uint32_t nextID;
    uint32_t sceneID;
    float TOTAL_TIME;
    std::vector< std::unique_ptr<Object> > _objects;
};
