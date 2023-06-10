#include "../include/ObjectFactory.hpp"

ObjectFactory* ObjectFactory::_instance = 0;

void ObjectFactory::createSphere(const Vector& pos, const float& mass, const float& radius){
    //scene->add(  std::make_unique<Sphere>( radius, mass, pos )  );
}

void ObjectFactory::createSphere(std::unique_ptr<Object> o){
    scene->add(  std::move(o) );
    scene->listAll();
}

ObjectFactory* ObjectFactory::getInstance(){

    if (!_instance) 
        _instance = new ObjectFactory();
    
    return _instance;
    
}