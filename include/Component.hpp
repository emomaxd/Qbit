#pragma once

#include <string>

class GameObject;

// Inherits from Object
class Component {

public:

    Component(){}
    ~Component(){}
    
    GameObject* gameObject;

    std::string name{"Component"};

    /// MULTIPLE COLLIDERS ALLOWED
    /// MULTIPLE TRANSFORM AND RB NOT ALLOWED etc.
    bool canBeMultiple{0};

    virtual void Update(){}

};