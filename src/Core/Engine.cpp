#include "Engine.hpp"

#include <iostream>
#include <thread>
#include <cmath>

#include <gtc/matrix_transform.hpp>

#define M_PI       3.14159265358979323846   // pi


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

bool isMousePressed = false;


glm::vec3 cameraPosition(0.0f, 0.0f, 5.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;

float vertical = 0.0f;
float horizontal = 0.0f;;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            horizontal = -1.0f;
        }
        if (key == GLFW_KEY_D) {
            horizontal = +1.0f;
        }
        if (key == GLFW_KEY_W) {
            vertical = +1.0f;
        }
        if (key == GLFW_KEY_S) {
            vertical = -1.0f;
        }
    }

    // Reset the variables when a key is released
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
            horizontal = 0.0f;
        }
        if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
            vertical = 0.0f;
        }
    }
   //    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {

            isMousePressed = true;
        }
        else if (action == GLFW_RELEASE) {

            isMousePressed = false;
        }
    }
    //ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    static double lastX = xPos;
    double xOffset = xPos - lastX;

    static double lastY = yPos;
    double yOffset = yPos - lastY;

    // camera z -> 50
    // slide speed -> 0.02f
    //const float slideSpeed = globalPosition.z / 1000;

    const float slideSpeed = 0.04f;

    if (isMousePressed) {
        if (xOffset != 0.0f) {
            //globalPosition.x += slideSpeed * xOffset;
            cameraTarget.x += slideSpeed * xOffset;
        }
        if (yOffset != 0.0f) {
            //globalPosition.y += slideSpeed * -yOffset;
            cameraTarget.y += slideSpeed * -yOffset;
        }
    }
    lastX = xPos;
    lastY = yPos;
    //ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
}

float lastX = 0.0f;
float lastY = 0.0f;
bool firstMouse = true;
static void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
   
    
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.2f;

    
    if (isMousePressed) {
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

    
        glm::vec3 front(0);
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }
}

static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yOffset;

    if (fov <= 1.0f)
        fov = 1.0f;
    
    if (fov >= 45.0f)
        fov = 45.0f;

    //ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


void Engine::InstantiateRectangle(const glm::vec3& pos, const glm::vec3& length, const Color& color) {

    Scene* activeScene = Engine::getActiveScene();

    auto entity = activeScene->createEntity();

    // position - rotation - scale
    activeScene->addComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(entity, glm::vec3{ pos }, { 0,0,0 }, { 1,1,1 });

    renderer->drawRectangle(pos, color, length.x, length.y, length.z);

}

/// TO DO 
/// Camera movement wit WASD(Currently it is moving but looks at the same point from another angle)
/// Change look direction while holding right mouse button down(Angle will be changed with mouse input)

void Engine::start(){
    
    auto GLFWwindow = window.getWindow();

   // glfwSetKeyCallback(GLFWwindow, key_callback);
    glfwSetScrollCallback(GLFWwindow, scrollCallback);
    glfwSetMouseButtonCallback(GLFWwindow, mouseButtonCallback);
    glfwSetCursorPosCallback(GLFWwindow, mouse_callback);

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

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), WIDTH / HEIGHT, 1.0f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

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

    for(float i = 0; i < 25; ++i) {
        float normalizedColor = 0.5f + 0.5f * std::sin(i / 25.0f * M_PI);  // Sine function for smoother transition
        InstantiateRectangle({ i, 0, 0 }, { length, length, length }, { normalizedColor * 2, normalizedColor * 3, normalizedColor, 1 });
    }

    while (!glfwWindowShouldClose(GLFWwindow))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(GLFWwindow);

        renderer->Clear();

        //angle += 1.0f;

        //scaleRatio += 0.02f * scaleDirection;

        if (scaleRatio >= maxScale || scaleRatio <= minScale)
        {
            scaleDirection *= -1.0f;
        }

        if (horizontal != 0.0f) {
            //cameraPosition.x += 0.05 * horizontal;
            //cameraTarget.x += 0.05 * horizontal;
        }
            
        
        if(vertical != 0.0f){
            //cameraPosition.y += 0.05 * vertical;
            //cameraTarget.y += 0.05 * vertical;
        }
        
        projectionMatrix = glm::perspective(glm::radians(fov), WIDTH / HEIGHT, 1.0f, 100.0f);
        viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));
        scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(scaleRatio));
        translationMatrix = glm::translate(glm::mat4(1), glm::vec3(translation));
        combinedMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
        shader.setMat4("Matrix", &combinedMatrix);


        renderer->render(shader);

        glfwSwapBuffers(GLFWwindow);
        glfwPollEvents();
    } 
    window.destroy();
}