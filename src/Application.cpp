#include "../include/Vector.hpp"
#include <iostream>
#include "../include/Box.hpp"

int main(){

    //Vector v(3,4,5);

    //std::cout<<v;


    float mass = 5;
    Box b( Vector(0,0,0), Vector(0,0,0), Vector(0, -10.0f * mass, 0), mass, 4, 4, 4 );
    for(float i=1;i<5; i += 1.0f / 60.0f )
    {
        std::cout<< "Time : " << i << "\n";
        b.update( 1.0f / 60.0f );
        b.print();
    }
    

    
    std::cin.get();
    return 0;
}
