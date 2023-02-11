#pragma once

class Object{
public:
    virtual void Update() = 0;
    virtual bool Colliding( const Object& other ) = 0; 
};