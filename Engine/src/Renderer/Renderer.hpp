#pragma once

#include <GL/glew.h>"
#include <GLFW/glfw3.h>
#include "../Scene/Scene.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "Shad.hpp"
#include "IndexBuffer.hpp"
#include "Camera.hpp"

#include <glm.hpp>

#include <iostream>
#include <vector>


class Renderer{
public:

    Renderer(){
        
    }

    ~Renderer(){
        std::cout << "RENDERER DESTRUCTED\n";
    }

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    void setScene(Scene* scene) { m_Scene = scene; }

    Scene* getScene() { return m_Scene; }

private:
    
    Scene* m_Scene{nullptr}; // Scene to be render - this could change in the runtime

};