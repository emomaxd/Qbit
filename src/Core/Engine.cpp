#include "Engine.hpp"

#include <iostream>
#include <thread>
#include <cmath>
#include "../Renderer/Texture.hpp"
#include "../../Dependencies/stb_image.h"
#include <random>
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

int g_width  = WIDTH;
int g_height = HEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //glViewport(0, 0, width, height);

    // Update ImGui layout
    ImGui::SetNextWindowSize(ImVec2(width * 0.20f, height), ImGuiCond_Always); // Adjust the size of the folders window
    ImGui::SetNextWindowSize(ImVec2(width * 0.8f, height), ImGuiCond_Always); // Adjust the size of the inspector panel

    g_width  = width;
    g_height = height;

}


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

std::vector<glm::vec3> generateRandomPositions(int n, float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    std::vector<glm::vec3> positions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(minX, maxX);
    std::uniform_real_distribution<float> disY(minY, maxY);
    std::uniform_real_distribution<float> disZ(minZ, maxZ);

    for (int i = 0; i < n; ++i) {
        float x = disX(gen);
        float y = disY(gen);
        float z = disZ(gen);
        positions.push_back(glm::vec3(x, y, z));
    }

    return positions;
}

void setupPointLights(const std::vector<glm::vec3> positions, Shader& shader) {
    for (size_t i = 0; i < positions.size(); ++i) {
        
        std::string prefix = "pointLights[" + std::to_string(i) + "].";

        shader.setVec3(prefix + "position", positions[i]);
        shader.setVec3(prefix + "ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        shader.setVec3(prefix + "diffuse",  glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3(prefix + "specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setUniformFloat(prefix + "constant", 1.0f);
        shader.setUniformFloat(prefix + "linear", 0.09f);
        shader.setUniformFloat(prefix + "quadratic", 0.032f);
    }
}


void Engine::start(){
    
    auto GLFWwindow = window.getWindow();

   // glfwSetKeyCallback(GLFWwindow, key_callback);
    glfwSetScrollCallback(GLFWwindow, scrollCallback);
    glfwSetMouseButtonCallback(GLFWwindow, mouseButtonCallback);
    glfwSetCursorPosCallback(GLFWwindow, mouse_callback);
    glfwSetFramebufferSizeCallback(GLFWwindow, framebuffer_size_callback);

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
    
    Shader LightingShader("src/Renderer/Shader/MultipleLights.glsl");
    Shader LightCubeShader("src/Renderer/Shader/LightCube.glsl");
    
    glm::mat4 rotationMatrix(1);
    glm::mat4 scaleMatrix(1);
    glm::mat4 translationMatrix(1);
    glm::mat4 modelMatrix(1);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)g_width / (float)g_height, 1.0f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    float angle = 0.0f;
    float scaleRatio = 1.0f;
    float translation = 0.0f;


    glm::mat4 combinedMatrix(1);

    //lighting setup

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    LightingShader.Bind();
    //LightingShader.setVec3("light.position",  lightPos);
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


    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    LightingShader.setUniformFloat("light.constant",  1.0f);
    LightingShader.setUniformFloat("light.linear",    0.09f);
    LightingShader.setUniformFloat("light.quadratic", 0.032f);

    int n = 240; // Number of positions
    float g_density = 20.0f;
    float minRange = -g_density; // Minimum range for positions
    float maxRange = g_density; // Maximum range for positions	

    // Generating random cube positions
    std::vector<glm::vec3> RandomcubePositions = generateRandomPositions(n, minRange, maxRange, minRange, maxRange, minRange, maxRange);

    // Generating random point light positions (n / 2.5)
    int npl = n / 2.5f;
    int numPointLights = npl > 60 ? 60 : npl ;
    std::vector<glm::vec3> RandompointLightPositions = generateRandomPositions(numPointLights, minRange, maxRange, minRange, maxRange, minRange, maxRange);

    int numCubes  = n;
    int numLights = numPointLights;
    float density = g_density;

    float inspectorWidth = g_width * 0.1f;

    float viewportX = 0;
    float viewportY = 0;
    float viewportWidth = 0;
    float viewportHeight = 0;
 

    while (!glfwWindowShouldClose(GLFWwindow))
    {


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        viewportX = 0;
        viewportY = 0;
        viewportWidth = g_width - g_width * 0.20f;
        viewportHeight = g_height;

        processInput(GLFWwindow);

        renderer->Clear(g_width, g_height);
        glViewport(viewportX, viewportY, viewportWidth, viewportHeight); // Set the size and position of the OpenGL viewport
        window.ImGuiNewFrame();

        projectionMatrix  = glm::perspective(glm::radians(fov), viewportWidth / viewportHeight, 1.0f, 100.0f);
        viewMatrix        = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        rotationMatrix    = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));

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
        
        // directional light
        LightingShader.setVec3("dirLight.direction",  glm::vec3(-0.2f, -1.0f, -0.3f));
        LightingShader.setVec3("dirLight.ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setVec3("dirLight.diffuse",  glm::vec3(0.4f, 0.4f, 0.4f));
        LightingShader.setVec3("dirLight.specular",  glm::vec3(0.5f, 0.5f, 0.5f));
        /*// point light 1
        LightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        LightingShader.setVec3("pointLights[0].ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setVec3("pointLights[0].diffuse",  glm::vec3(0.8f, 0.8f, 0.8f));
        LightingShader.setVec3("pointLights[0].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setUniformFloat("pointLights[0].constant", 1.0f);
        LightingShader.setUniformFloat("pointLights[0].linear", 0.09f);
        LightingShader.setUniformFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        LightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        LightingShader.setVec3("pointLights[1].ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setVec3("pointLights[1].diffuse",  glm::vec3(0.8f, 0.8f, 0.8f));
        LightingShader.setVec3("pointLights[1].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setUniformFloat("pointLights[1].constant", 1.0f);
        LightingShader.setUniformFloat("pointLights[1].linear", 0.09f);
        LightingShader.setUniformFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        LightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        LightingShader.setVec3("pointLights[2].ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setVec3("pointLights[2].diffuse",  glm::vec3(0.8f, 0.8f, 0.8f));
        LightingShader.setVec3("pointLights[2].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setUniformFloat("pointLights[2].constant", 1.0f);
        LightingShader.setUniformFloat("pointLights[2].linear", 0.09f);
        LightingShader.setUniformFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        LightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        LightingShader.setVec3("pointLights[3].ambient",  glm::vec3(0.05f, 0.05f, 0.05f));
        LightingShader.setVec3("pointLights[3].diffuse",  glm::vec3(0.8f, 0.8f, 0.8f));
        LightingShader.setVec3("pointLights[3].specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setUniformFloat("pointLights[3].constant", 1.0f);
        LightingShader.setUniformFloat("pointLights[3].linear", 0.09f);
        LightingShader.setUniformFloat("pointLights[3].quadratic", 0.032f);
        */
        setupPointLights(RandompointLightPositions, LightingShader);
        // spotLight
        LightingShader.setVec3("spotLight.position", cameraPosition);
        LightingShader.setVec3("spotLight.direction", cameraFront);
        LightingShader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        LightingShader.setVec3("spotLight.diffuse",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setVec3("spotLight.specular",  glm::vec3(1.0f, 1.0f, 1.0f));
        LightingShader.setUniformFloat("spotLight.constant", 1.0f);
        LightingShader.setUniformFloat("spotLight.linear", 0.09f);
        LightingShader.setUniformFloat("spotLight.quadratic", 0.032f);
        LightingShader.setUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        LightingShader.setUniformFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));     

            // IMGUI
            ImGui::SetNextWindowPos(ImVec2(g_width * 0.80f, 0), ImGuiCond_Always); // Adjust the position of the inspector panel
            ImGui::SetNextWindowSize(ImVec2(g_width * 0.20f, g_height), ImGuiCond_Always); // Set the size of the inspector panel

            ImGui::Begin("Inspector Panel", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);       
            

            ImGui::Text("Object count : %d", n + numPointLights);
            // Declare a variable to store the cube count
            

            // In your ImGui panel
            ImGui::SliderInt("Cube Count", &numCubes, 0, 100000);
            ImGui::SliderInt("Light Count", &numLights, 0, 60);

            ImGui::SliderFloat("Density", &density, 0.0f, 1000.0f);

            // Update position range if it has changed
            if (density != g_density) {
                g_density = density; 
                RandomcubePositions = generateRandomPositions(n, -g_density, g_density, -g_density, g_density, -g_density, g_density);
                RandompointLightPositions = generateRandomPositions(numPointLights, -g_density, g_density, -g_density, g_density, -g_density, g_density);
                setupPointLights(RandompointLightPositions, LightingShader);
            }

            // Update cube count if it has changed
            if (numCubes != n) {
                n = numCubes;
                RandomcubePositions = generateRandomPositions(n, -g_density, g_density, -g_density, g_density, -g_density, g_density);
            }

            if(numLights != numPointLights){
                numPointLights = numLights;
                RandompointLightPositions = generateRandomPositions(numPointLights, -g_density, g_density, -g_density, g_density, -g_density, g_density);
                setupPointLights(RandompointLightPositions, LightingShader);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

           
            
            ImGui::End();

        /*
            // Set up ImGui layout for the folders window at the bottom
            ImGui::SetNextWindowPos(ImVec2(0, g_height * 0.75f), ImGuiCond_Always); // Adjust the position of the folders window
            ImGui::SetNextWindowSize(ImVec2(g_width, g_height * 0.25f), ImGuiCond_Always); // Set the size of the folders window

            // Begin ImGui window for the folders window
            ImGui::Begin("Folders", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            // Add ImGui content for folders window

            // End ImGui window for the folders window
            ImGui::End();
        */
            
        // IMGUI

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        /// Draw the cube
        for(unsigned int i = 0; i < n; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, RandomcubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            LightingShader.setMat4("model", &model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }   

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
        for (unsigned int i = 0; i < numPointLights; i++)
        {
            modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, RandompointLightPositions[i]);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f)); // Make it a smaller cube
            LightCubeShader.setMat4("model", &modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        
        window.ImGuiRender();

        window.SwapBuffers();

    } 
    window.Cleanup();
}