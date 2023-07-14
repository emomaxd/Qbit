#pragma once

#include <memory>
#include <iostream>

#include "Vector.hpp"


class Object
{
public:
    
    Object() {}
    Object(float  mass, Vector position);
    virtual ~Object();

    void addForce( const Vector& F );

    void removeForce( const Vector& F );

    virtual bool isColliding( const std::unique_ptr<Object>& ) = 0;
    virtual void handleCollision( const std::unique_ptr<Object>& ) = 0;

    Vector calcAcceleration( const Vector& F, const float& mass ) const;
    Vector calcMomentum( const Vector& V, const float& mass ) const;

    virtual void update( const float& dt ) = 0;

    virtual void print() = 0;



    // GETTER SETTER

    inline uint64_t getID() const { return ID; }
    inline void setID(uint64_t id) { ID = id; }
    
    
    inline float getMass() const { return _mass; }
    inline void setMass(float mass) { _mass = mass; }
    
    
    inline Vector getPosition() const { return _position; }
    inline void setPosition(const Vector& position) { _position = position; }
    
    
    inline Vector getVelocity() const { return _velocity; }
    inline void setVelocity(const Vector& velocity) { _velocity = velocity; }
    
   
    inline Vector getNetForce() const { return _netForce; }
    inline void setNetForce(const Vector& netForce) { _netForce = netForce; }


protected:

    uint64_t ID{};
    static uint64_t count;
    float  _mass{};
    Vector _position{};
    Vector _velocity{};
    Vector _netForce{};
    Vector _rotation{};
};

