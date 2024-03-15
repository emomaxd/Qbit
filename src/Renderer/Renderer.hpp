#pragma once

#include "../../Dependencies/GLEW/include/GL/glew.h"
#include "../../Dependencies/GLFW/include/GLFW/glfw3.h"
#include "../Scene/Scene.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "Camera.hpp"

#include <glm.hpp>

#include <iostream>
#include <vector>

class Texture;

struct Position {
    glm::vec3 X, Y, Z;
};

struct Color {
    glm::vec4 color;
};

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 textureCoordinates;
};

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