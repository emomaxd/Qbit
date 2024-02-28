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
        vertexes.reserve(5000);
    }
    Renderer(Scene* scene) : scene(scene){
    }

    ~Renderer(){
        std::cout << "RENDERER DESTRUCTED\n";
    }

    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    void render(const Shader& shader);

    void Clear();

    void drawTriangle(const Position& position, const Color& color, const Texture* texture = nullptr);

    void drawRectangle(const glm::vec3& position, const Color& color, float width, float height, float depth, const Texture* texture = nullptr);

    GLFWwindow* getWindow(){ return window; }

    void setScene(Scene* scene) { this->scene = scene; }

    Scene* getScene() { return scene; }

    std::vector<Vertex> vertexes;  // This vector is for holding all the vertexes then we will draw everything with only 1 draw call
    std::vector<unsigned int> indices;

private:
    
    Scene* scene{nullptr}; // Scene to be render - this could change in the runtime
    GLFWwindow* window{nullptr}; // This one will be deleted only the engine class will be responsible for window operations
    Shader* activeShader{}; // 
    Camera mainCamera;

   
    

};