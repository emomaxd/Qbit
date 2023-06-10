#pragma once

#include "Sphere.hpp"
#include "Scene.hpp"

class ObjectFactory{
public:
    void createSphere(const Vector& pos, const float& mass, const float& radius);
    void createSphere(std::unique_ptr<Object> o);

    static ObjectFactory* getInstance();

    ~ObjectFactory(){
        delete this;
    }
       
private:
    static ObjectFactory* _instance;
    Scene* scene;
    ObjectFactory(){scene = Scene::getInstance();}

};


