#pragma once

#include <string>

class GameObject;

// Inherits from Object
class Component {

public:

    GameObject* gameObject;

    std::string name;

    virtual void Update(){}

};