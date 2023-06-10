#include "../include/InputHandler.hpp"

InputHandler* InputHandler::_instance = 0;

void InputHandler::listen(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        
        Vector2 mousePos = GetMousePosition();
        
        //std::cout<<mousePos.x << "   ";
        //std::cout<<mousePos.y << "\n";

        Sphere* temp = new Sphere(30, 5, Vector(mousePos.x, mousePos.y,0));
        temp->setVelocity({30,0,0});
        std::unique_ptr<Object> objectPtr(temp);
        ObjectFactory::getInstance()->createSphere(std::move(objectPtr));
        
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        
        Vector2 mousePos = GetMousePosition();
        
        //std::cout<<mousePos.x << "   ";
        //std::cout<<mousePos.y << "\n";

        Sphere* temp = new Sphere(30, 5, Vector(mousePos.x, mousePos.y,0));
        temp->setVelocity({-30,0,0});
        std::unique_ptr<Object> objectPtr(temp);
        ObjectFactory::getInstance()->createSphere(std::move(objectPtr));
        
        
    }


}