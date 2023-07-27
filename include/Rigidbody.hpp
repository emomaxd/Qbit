#include "../include/Vector.hpp"

class Rigidbody{

public:

    bool isKinematic;
    bool useGravity;
    float mass;
    Vector position; /// ? TRANSFORM COMPONENT ATTR.?
    Vector rotation; /// ?           ""
    Vector velocity;
    
};