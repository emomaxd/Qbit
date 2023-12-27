#include "Renderer.hpp"

#include <iostream>


void Renderer::Clear() {
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::drawTriangle(const Position& position, const Color& color) {

    const glm::vec3 X = position.X;
    const glm::vec3 Y = position.Y;
    const glm::vec3 Z = position.Z;

    float vertices[] = {
        X.x, X.y, X.z,     // Vertex 0
        Y.x, Y.y, Y.z, // Vertex 1
        Z.x, Z.y, Z.z  // Vertex 2
    };

    // Define the indices for the triangle
    unsigned int indices[] = {
        0, 1, 2  // Triangle indices
    };

    // Assuming vertexes is your container for vertices (use whatever is appropriate)
    const size_t numIndices = sizeof(indices) / sizeof(indices[0]);
    for (size_t i = 0; i < numIndices; ++i) {
        const unsigned int index = indices[i];
        vertexes.push_back({ { vertices[index * 3], vertices[index * 3 + 1], vertices[index * 3 + 2] }, { color.R, color.G, color.B, color.A } });
    }
    
}

void Renderer::drawRectangle(const glm::vec3& position, const Color& color, float width, float height, float depth) {

    const float X = position.x;
    const float Y = position.y;
    const float Z = position.z;

    float vertices[] = {
        X - width, Y + height, Z + depth,  // 0: Top Left Front
        X + width, Y + height, Z + depth,  // 1: Top Right Front
        X + width, Y - height, Z + depth,  // 2: Bottom Right Front
        X - width, Y - height, Z + depth,  // 3: Bottom Left Front

        X - width, Y + height, Z - depth,  // 4: Top Left Back
        X + width, Y + height, Z - depth,  // 5: Top Right Back
        X + width, Y - height, Z - depth,  // 6: Bottom Right Back
        X - width, Y - height, Z - depth   // 7: Bottom Left Back
    };

    // Define the indices for the rectangle
    unsigned int indices[] = {
        0, 1, 2,    // Front face
        2, 3, 0,
        1, 5, 6,    // Right face
        6, 2, 1,
        5, 4, 7,    // Back face
        7, 6, 5,
        4, 0, 3,    // Left face
        3, 7, 4,
        4, 5, 1,    // Top face
        1, 0, 4,
        3, 2, 6,    // Bottom face
        6, 7, 3
    };

    // Assuming vertexes is your container for vertices (use whatever is appropriate)
    const size_t numIndices = sizeof(indices) / sizeof(indices[0]);
    for (size_t i = 0; i < numIndices; ++i) {
        const unsigned int index = indices[i];
        vertexes.push_back({ { vertices[index * 3], vertices[index * 3 + 1], vertices[index * 3 + 2] }, { color.R, color.G, color.B, color.A } });
    }
}

void Renderer::render(const Shader& shader){
   
    Clear();
    shader.Bind();

    VertexArray VAO;
    VertexBuffer VBO(vertexes.data(), vertexes.size() * sizeof(Vertex));
    VertexBufferLayout layout;
    layout.Push<float>(3); // position - glm::vec3 - 3 floats
    layout.Push<float>(4); // color    - glm::vec4 - 4 floats

    VAO.AddBuffer(VBO, layout);

    // Index Buffer Setup
    const size_t maxIndices = 1000;
    unsigned int indices[maxIndices];
    for (size_t i = 0; i < vertexes.size(); ++i)
        indices[i] = static_cast<unsigned int>(i);

    IndexBuffer IBO(indices, vertexes.size());

    // Draw
    glDrawElements(GL_TRIANGLES, vertexes.size(), GL_UNSIGNED_INT, nullptr);

}
