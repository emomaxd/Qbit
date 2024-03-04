#include "Engine.hpp"

#include <iostream>
#include <thread>
#include <cmath>
#include "../Renderer/Texture.hpp"
#include "../../Dependencies/stb_image.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define M_PI       3.14159265358979323846   // pi




template <typename T>
static void updateSystem(T* system){
    system->Update();
}


Engine::Engine(Renderer* renderer, Scene* initialScene){
        
    //window.Init();
        
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


glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
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
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
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
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

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
    ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
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
    ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
}

static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yOffset;

    if (fov <= 1.0f)
        fov = 1.0f;
    
    if (fov >= 45.0f)
        fov = 45.0f;

    ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
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


void Engine::InstantiateRectangle(const glm::vec3& pos, const glm::vec3& length, const Color& color, const Texture* texture) {

    Scene* activeScene = Engine::getActiveScene();

    auto entity = activeScene->createEntity();

    // position - rotation - scale
    activeScene->addComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(entity, glm::vec3{ pos }, { 0,0,0 }, { 1,1,1 });
    // Color
    activeScene->addComponent<Color, glm::vec4>(entity, glm::vec4{color.color});
    // Texture

    renderer->drawRectangle(pos, color, length.x, length.y, length.z, texture);

}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


void Engine::start(){
    
    auto GLFWwindow = window.getWindow();

   // glfwSetKeyCallback(GLFWwindow, key_callback);
    glfwSetScrollCallback(GLFWwindow, scrollCallback);
    glfwSetMouseButtonCallback(GLFWwindow, mouseButtonCallback);
    glfwSetCursorPosCallback(GLFWwindow, mouse_callback);

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

    stbi_set_flip_vertically_on_load(1);
    glEnable(GL_DEPTH_TEST);

    //Shader setup
    // Basic & Essential shader for rendering with position and color settings
    Shader shader("src/Renderer/Shader/BasicShader.glsl");
    
    Shader LightingShader("src/Renderer/Shader/BasicLighting.glsl");
    Shader LightCubeShader("src/Renderer/Shader/LightCube.glsl");

    LightCubeShader.Bind();
    LightCubeShader.AddUniform("model");
    LightCubeShader.AddUniform("view");
    LightCubeShader.AddUniform("projection");

    LightingShader.Bind();
    LightingShader.AddUniform("model");
    LightingShader.AddUniform("view");
    LightingShader.AddUniform("projection");

    LightingShader.AddUniform("material.ambient");
    LightingShader.AddUniform("material.diffuse");
    LightingShader.AddUniform("material.specular");
    LightingShader.AddUniform("material.shininess");
    LightingShader.AddUniform("light.position");
    LightingShader.AddUniform("light.ambient");
    LightingShader.AddUniform("light.diffuse");
    LightingShader.AddUniform("light.specular");
    
    glm::mat4 rotationMatrix(1);
    glm::mat4 scaleMatrix(1);
    glm::mat4 translationMatrix(1);
    glm::mat4 modelMatrix(1);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), WIDTH / HEIGHT, 1.0f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    float angle = 0.0f;
    float scaleRatio = 1.0f;
    float translation = 0.0f;


    glm::mat4 combinedMatrix(1);

    //lighting setup

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    LightingShader.Bind();
    LightingShader.setVec3("light.position",  lightPos);
    LightingShader.setUniformInteger("material.diffuse", 0);
    LightingShader.setUniformInteger("material.specular", 1);

    

    ImGuiIO& io = ImGui::GetIO();

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    /// Texture setup    

    unsigned int diffuseMap = loadTexture("Assets/container2.png");
    unsigned int specularMap = loadTexture("Assets/container2_specular.png");
    unsigned int lightCubeTexture = loadTexture("Assets/redstone_lamp1.jpg");



    glm::vec3 lightColor(1);
    // Define orbit parameters
    float orbitRadius = 2.0f;
    float orbitSpeed = 1.0f;
    float orbitRadiusY = 1.0f; // Height of the orbit


    /// Object rotation
    glm::vec3 rotation(0);
    const float rotationSpeed = 0.2f;

    while (!glfwWindowShouldClose(GLFWwindow))
    {


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Update light position for orbit
        float orbitAngle = glfwGetTime() * orbitSpeed;
        float lightPosX = orbitRadius * cos(orbitAngle);
        float lightPosY = orbitRadiusY * sin(orbitAngle); // Adjusted for y-axis orbit
        float lightPosZ = orbitRadius * sin(orbitAngle);

        lightPos = glm::vec3(lightPosX, lightPosY, lightPosZ);
    
        
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); 
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
        
        rotation.x += deltaTime * rotationSpeed;
        rotation.y += deltaTime * rotationSpeed;
        rotation.z += deltaTime * rotationSpeed;
        

        processInput(GLFWwindow);

        renderer->Clear();
        window.ImGuiNewFrame();

        projectionMatrix  = glm::perspective(glm::radians(fov), WIDTH / HEIGHT, 1.0f, 100.0f);
        viewMatrix        = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        rotationMatrix    = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));
        rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis rotation
        rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis rotation
        rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis rotation

        scaleMatrix       = glm::scale(glm::mat4(1), glm::vec3(scaleRatio));
        translationMatrix = glm::translate(glm::mat4(1), glm::vec3(translation));
        modelMatrix       = translationMatrix * rotationMatrix * scaleMatrix;        

        LightingShader.Bind();
        LightingShader.setMat4("model",      &modelMatrix);
        LightingShader.setMat4("view",       &viewMatrix);
        LightingShader.setMat4("projection", &projectionMatrix);
        LightingShader.setVec3("viewPos", cameraPosition);

        LightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setVec3("material.specular", glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setUniformFloat("material.shininess", 32.0f);
        
        LightingShader.setVec3("light.position", lightPos);
        LightingShader.setVec3("light.ambient", ambientColor);
        LightingShader.setVec3("light.diffuse", diffuseColor);
        LightingShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // IMGUI

            ImGui::Begin("Inspector Panel");       
            
            // Adjust light color
            ImGui::SliderFloat3("Light Color", glm::value_ptr(lightColor), 1, 255);

            // Adjust ambient color
            ImGui::SliderFloat3("Ambient Color", glm::value_ptr(ambientColor), 1, 255);
            
            ImGui::End();
            
        // IMGUI

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        /// Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        modelMatrix    = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));
        modelMatrix = glm::translate(modelMatrix, lightPos);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        
        glBindVertexArray(lightCubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lightCubeTexture);
        
        LightCubeShader.Bind();
        LightCubeShader.setMat4("model",      &modelMatrix);
        LightCubeShader.setMat4("view",       &viewMatrix);
        LightCubeShader.setMat4("projection", &projectionMatrix);

        /// Draw the light as a cube
        glDrawArrays(GL_TRIANGLES, 0, 36);


        
        window.ImGuiRender();

        window.SwapBuffers();

    } 
    window.Cleanup();
}