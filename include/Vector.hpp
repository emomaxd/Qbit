#pragma once
#include <cmath>
#include <iostream>



    class Vector{
        private:
            
            float _x, _y, _z ;
            
        public:

            Vector();
            Vector( const float& x, const float& y, const float& z );
            
            float getX() const ;
            float getY() const ;
            float getZ() const ;
            float getMagnitude() const ;

            void setX( const float& n );
            void setY( const float& n );
            void setZ( const float& n );
            
            Vector operator+( const Vector& other ) const ;
            Vector operator+( const float& n ) const ;

            Vector operator-( const Vector& other ) const ;
            Vector operator-( const float& n ) const ;

            friend std::ostream& operator<<( std::ostream& o, const Vector& v );

            friend float dotProduct( const Vector& a, const Vector& b );
            friend Vector crossProduct( const Vector& a, const Vector& b );
            Vector GET_UNIT_VECTOR();
    };

