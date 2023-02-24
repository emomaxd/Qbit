#pragma once

#include <memory>

#include "Vector.hpp"

#define BOX 0
#define SPHERE 1

class Object
{
public:
    
    Object() {}
    Object(float  _mass, Vector _position, Vector _velocity, Vector _netForce);
    virtual ~Object();

    void addForce( const Vector& F );
    void addForce( const Vector& F, const Vector& applyPosition );

    void removeForce( const Vector& F );

    virtual bool isColliding( const std::unique_ptr<Object>& ) = 0;
    virtual void handleCollision( const std::unique_ptr<Object>& ) = 0;

    Vector calcAcceleration( const Vector& F, const float& mass ) const;
    Vector calcMomentum( const Vector& V, const float& mass ) const;

    virtual void update( const float& dt ) = 0;

    virtual void print();



    // GETTER SETTER

    uint64_t getID() const { return ID; }
    void setID(uint64_t id) { ID = id; }
    
    
    float getMass() const { return _mass; }
    void setMass(float mass) { _mass = mass; }
    
    
    Vector getPosition() const { return _position; }
    void setPosition(const Vector& position) { _position = position; }
    
    
    Vector getVelocity() const { return _velocity; }
    void setVelocity(const Vector& velocity) { _velocity = velocity; }
    
   
    Vector getNetForce() const { return _netForce; }
    void setNetForce(const Vector& netForce) { _netForce = netForce; }

protected:
    uint8_t TYPE;
    uint64_t ID;
    float  _mass;
    Vector _position;
    Vector _velocity;
    Vector _netForce;
    
};