#pragma once

#include "../Scene/Scene.hpp"
#include "../Scene/Components.hpp"

namespace EMax3D{


    class Physic{
            
    public:
        Physic();
        Scene* m_scene;
        float m_gravity = 0.0f;

        void Update();
            
    private:
        const float gravityConstant = 9.8f;
        bool applyGravity{true};
    


    };

}