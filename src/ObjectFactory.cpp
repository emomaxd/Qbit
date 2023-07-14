#include "../include/ObjectFactory.hpp"

ObjectFactory* ObjectFactory::_instance = nullptr;

void ObjectFactory::createSphere(const Vector& pos, const float& mass, const float& radius){
    scene->add(  std::make_unique<Sphere>( radius, mass, pos )  );
    //scene->listAll();
}

void ObjectFactory::createSphere(std::unique_ptr<Object> o){
    scene->add(  std::move(o) );
    //scene->listAll();
}

ObjectFactory* ObjectFactory::getInstance(){

    if (!_instance) 
        _instance = new ObjectFactory();
    
    return _instance;
    
}