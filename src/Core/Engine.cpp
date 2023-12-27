#include "Engine.hpp"

#include <iostream>
#include <thread>

#include <gtc/matrix_transform.hpp>


template <typename T>
static void updateSystem(T* system){
    system->Update();
}


Engine::Engine(Renderer* renderer, Scene* initialScene){
        
    window.init();
        
    Engine::activeScene=initialScene;
    scenes.push_back(initialScene);

    this->renderer = renderer;
        
}

Engine::~Engine(){

    std::cout << "ENGINE DESTRUCTED\n";

    for (auto s : scenes)
        delete s;

    delete renderer;

}

const float length = 0.08f;
const float ldtwo = length / 2;


glm::vec3 globalPosition(0.0f, 0.0f, 5.0f);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            globalPosition.x -= 1.0f;
        }
        if (key == GLFW_KEY_D) {
            globalPosition.x += 1.0f;
        }
        if (key == GLFW_KEY_W) {
            globalPosition.y += 1.0f;
        }
        if (key == GLFW_KEY_S) {
            globalPosition.y -= 1.0f;
        }

    }
    
}





void Engine::start(){
    
    auto GLFWwindow = window.getWindow();

    glfwSetKeyCallback(GLFWwindow, key_callback);

    //Shader setup

    // Basic & Essential shader for rendering with position and color settings
    Shader shader("src/Renderer/Shader/BasicShader.glsl");

    //shader.AddUniform("color");
    shader.AddUniform("Matrix");

    shader.Bind();

    auto& v = renderer->vertexes;

    float vertices[] = {


       -length / 2, -length / 2, -length / 2,
       length / 2, -length / 2, -length / 2,
       length / 2, -length / 2, length / 2,
       - length / 2, -length / 2, length / 2,

       - length / 2, length / 2, -length / 2,
       length / 2, length / 2, -length / 2,
       length / 2, length / 2, length / 2,
       -length / 2, length / 2, length / 2,


    };


    VertexArray vao;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);

    vao.AddBuffer(vb, layout);

    GLuint indices[] = {
        7,3,2,

        7,2,6,

        
        6,2,1,
        
        6,1,5,
        
        
        4,7,6,
         
        4,6,5,
         
         
        0,3,2,
         
        0,2,1,

         
        4,0,1,
         
        4,1,5,

                 
        7,3,0,
         
        7,0,4,

    };

    IndexBuffer ib(indices, 36);
    
    
    glm::mat4 rotationMatrix(1);
    glm::mat4 scaleMatrix(1);
    glm::mat4 translationMatrix(1);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 1.0f, 100.0f);

    glm::vec3 cameraPosition = globalPosition;
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    float angle = 0.0f;
    float scaleRatio = 1.0f;
    float translation = 0.0f;
    float scaleDirection = 1.0f; 
    float translationDirection = 1.0f; 

    glm::mat4 combinedMatrix(1);

    const float minScale = 1.0f;
    const float maxScale = 10.0f;
    const float minTranslation = -300.0f; 
    const float maxTranslation = 300.0f;

    //renderer->drawTriangle({ {-ldtwo,0,0}, {-ldtwo,ldtwo,0} ,{0,0,0} }, { 1,0,0, 1 });
    //renderer->drawTriangle({ {-ldtwo,ldtwo,0}, {0,ldtwo,0} ,{0,0,0} }, { 1,0.6,0, 1 });



   renderer->drawRectangle({ 0,0,0 }, { 1,0,0,1 }, length, length, length);
   renderer->drawRectangle({ 0.08, 0.08,0 }, { 1,0.6,0.2,1 }, length, length, length);

    while (!glfwWindowShouldClose(GLFWwindow))
    {
        renderer->Clear();

        angle += 1.0f;

        scaleRatio += 0.02f * scaleDirection;

        if (scaleRatio >= maxScale || scaleRatio <= minScale)
        {
            scaleDirection *= -1.0f;
        }

        cameraPosition = globalPosition;
        viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));
        scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(scaleRatio));
        translationMatrix = glm::translate(glm::mat4(1), glm::vec3(translation));
        combinedMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
        shader.setMat4("Matrix", &combinedMatrix);


        //renderer->draw(vao, ib, shader);
        renderer->render(shader);

        glfwSwapBuffers(GLFWwindow);
        glfwPollEvents();
    } 
    window.destroy();
}