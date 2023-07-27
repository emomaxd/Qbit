#include "../include/InputHandler.hpp"


#include "../include/Engine.hpp"

#include "../include/Sphere.hpp"


InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::getInstance() {
    if (!_instance) 
        return new InputHandler();
        
    return _instance;
}

void InputHandler::createSphereWithVelocity(Vector velocity, int radius, int mass) {
    Vector2 mousePos = GetMousePosition();
    Sphere* temp = new Sphere(radius, mass, Vector(mousePos.x, mousePos.y, 0));
    temp->setVelocity(velocity);
    std::unique_ptr<Object> objectPtr(temp);
    
    Engine::getActiveScene()->add( std::move(objectPtr) );

}


void InputHandler::listen(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        createSphereWithVelocity({-400, 360 ,0}, 30, 1200);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        createSphereWithVelocity({-203, -230, 0}, 30 ,120);
    }
}