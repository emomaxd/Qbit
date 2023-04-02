#pragma once

#include <cmath>
#include <iostream>


class Vector
{
private:
            
    float _x, _y, _z ;
            
public:
    Vector();
    Vector( const float& x, const float& y, const float& z );
    
    
    inline float getX() const { return _x; }
    inline float getY() const { return _y; }
    inline float getZ() const { return _z; }


    inline void setX( const float& n ){ _x = n; }
    inline void setY( const float& n ){ _y = n; }
    inline void setZ( const float& n ){ _z = n; }

    float getMagnitude() const { return sqrt( _x*_x + _y*_y + _z*_z ); }
    

    Vector  operator+( const Vector& other ) const ;
    Vector  operator+( const float& n ) const ;
    Vector& operator+=( const Vector& other ) ;
    Vector& operator+=( const float& n ) ;
    Vector  operator-( const Vector& other ) const ;
    Vector  operator-( const float& n ) const ;
    Vector& operator-=( const Vector& other ) ;
    Vector& operator-=( const float& n ) ;
    Vector  operator/( const float& n ) const ;
    Vector  operator*( const float& n ) const ; 
    friend Vector operator*( const float& n, const Vector& v) ;
    friend std::ostream& operator<<( std::ostream& o, const Vector& v ) ;
    friend float dotProduct( const Vector& a, const Vector& b );
    friend Vector crossProduct( const Vector& a, const Vector& b );
    Vector normalized();
};

