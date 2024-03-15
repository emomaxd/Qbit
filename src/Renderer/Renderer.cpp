#include "Renderer.hpp"

#include <iostream>


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);
}

