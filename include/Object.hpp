#pragma once
#include "Vector.hpp"

enum class OBJECT_TYPE
{
        BOX,
        CIRCLE 
};

class Object{

public:

    virtual void update( const float& dt ) = 0;
    virtual bool isColliding( const Object& other ) = 0; 
    virtual void applyForce( const Vector& force ) = 0;

};