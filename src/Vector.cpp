#include "../include/Vector.hpp"



// CONSTRUCTORS
Vector::Vector() : _x(0), _y(0), _z(0) {}

Vector::Vector( const float& x, const float& y, const float& z ) : _x(x), _y(y), _z(z) {} 



// OPERATOR OVERLOADS
Vector Vector::operator+( const Vector& other ) const
{
    return Vector( _x + other._x, _y + other._y, _z + other._z );
}

Vector Vector::operator+( const float& n ) const
{
    return Vector( _x + n, _y + n, _z + n );
}

Vector& Vector::operator+=( const Vector& other ) { _x += other._x; _y += other._y; _z += other._z; return *this; } 
Vector& Vector::operator+=( const float& n ) { _x += n; _y += n; _z += n; return *this;}

Vector Vector::operator-( const Vector& other ) const
{
    return Vector( _x - other._x, _y - other._y, _z - other._z );
}

Vector Vector::operator-( const float& n ) const
{
    return Vector(_x - n, _y - n, _z - n );
}

Vector& Vector::operator-=( const Vector& other ) { _x -= other._x; _y -= other._y; _z -= other._z; return *this; } 
Vector& Vector::operator-=( const float& n ) { _x -= n; _y -= n; _z -= n; return *this;}


Vector Vector::operator/( const float& n ) const
{
    return Vector( (float)_x / n, (float)_y / n, (float)_z / n );
}

Vector Vector::operator*( const float& n ) const
{
    return Vector( _x * n, _y * n, _z * n );
}


Vector operator*( const float& n, const Vector& v)
{
    return Vector( v._x * n, v._y * n, v._z * n );
}


std::ostream& operator<<( std::ostream& o, const Vector& v )
{
    return o << "X : " << v._x << "\tY : " << v._y << "\tZ : " << v._z;
}




// OTHER FUNCTIONS
float dotProduct( const Vector& a, const Vector& b ) 
{
    return ( a._x * b._x + a._y * b._y + a._z * b._z );
}

Vector crossProduct( const Vector& a, const Vector& b ) 
{
    return Vector(      a._y * b._z - a._z * b._y
    ,                   a._z * b._x - a._x * b._z
    ,                   a._x * b._y - a._y * b._x                   );
}

Vector Vector::normalized(){ return Vector( _x/getMagnitude(), _y/getMagnitude(), _z/getMagnitude() ); }
        