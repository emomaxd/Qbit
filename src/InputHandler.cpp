#include "../include/InputHandler.hpp"



InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::getInstance() {
    if (!_instance) 
        return new InputHandler();
        
    return _instance;
}

static void createSphereWithVelocity(Vector velocity, int radius, int mass) {
    Vector2 mousePos = GetMousePosition();
    Sphere* temp = new Sphere(radius, mass, Vector(mousePos.x, mousePos.y, 0));
    temp->setVelocity(velocity);
    std::unique_ptr<Object> objectPtr(temp);
    ObjectFactory::getInstance()->createSphere(std::move(objectPtr));
}


void InputHandler::listen(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        createSphereWithVelocity({-40, 60 ,0}, 30, 1200);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        createSphereWithVelocity({-20, -20, 0}, 30 ,1200);
    }
}