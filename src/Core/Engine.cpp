#include "Engine.hpp"

#include <iostream>
#include <thread>
#include <cmath>
#include "../../Dependencies/stb_image.h"
#include <random>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


#define M_PI       3.14159265358979323846   // pi


Engine::Engine(){
        
    m_Renderer = new Renderer();

    Scene* tempScene = new Scene();
    AddScene(tempScene);
    s_ActiveScene = tempScene;
}



Engine::~Engine(){

    std::cout << "ENGINE DESTRUCTED\n";

    for (auto s : m_Scenes)
        delete s.second;

    delete m_Renderer;

}

bool isMousePressed = false;


glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float roll = 0.0f;
float pitch = 0.0f;
float fov = 45.0f;

float vertical = 0.0f;
float horizontal = 0.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    Window::s_WindowWidth = width;
    Window::s_WindowHeight = height;

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

        if (key == GLFW_KEY_A || key == GLFW_KEY_D)
            horizontal = 0.0f;

        if (key == GLFW_KEY_W || key == GLFW_KEY_S)
            vertical = 0.0f;
    }

    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS)
            isMousePressed = true;
        else if (action == GLFW_RELEASE)
            isMousePressed = false;
    }
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

    static double lastX = xPos;
    double xOffset      = xPos - lastX;

    static double lastY = yPos;
    double yOffset      = yPos - lastY;

    const float slideSpeed = 0.04f;

    if (isMousePressed) {
        if (xOffset != 0.0f)
            cameraTarget.x += slideSpeed * xOffset;
        if (yOffset != 0.0f)
            cameraTarget.y += slideSpeed * -yOffset;
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

    auto cam = Engine::s_ActiveScene->m_EntityVector[0];
    auto transform = Engine::s_ActiveScene->GetComponent<Transform>(cam);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        transform->position += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        transform->position -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        transform->position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        transform->position += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}


unsigned int loadTexture(char const * path)
{
    stbi_set_flip_vertically_on_load(1);
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

unsigned int loadCubemap(std::vector<std::string> faces)
{
    stbi_set_flip_vertically_on_load(0);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}




// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

unsigned int planeVAO;
void renderScene(Shader &shader)
{
    // floor
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", &model);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", &model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    model = glm::scale(model, glm::vec3(0.5f));
    shader.setMat4("model", &model);
    renderCube();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.25));
    shader.setMat4("model", &model);
    renderCube();
}



void DrawCameraInspector(Camera& camera) {
    ImGui::Text("Camera");

    ImGui::Combo("Projection", reinterpret_cast<int*>(&camera.projection), "Perspective\0Orthographic\0");

    ImGui::DragFloat("Field of View", &fov, 1.0f, 1.0f, 45.0f);
    ImGui::ColorEdit4("Clear Color", glm::value_ptr(camera.clearColor));


    // Here you can add more controls for other camera properties if needed
}


void Engine::start(){
    
    auto GLFWwindow = m_Window.GetWindow();

    auto scene = s_ActiveScene;

    auto& entityVector = scene->m_EntityVector;

    auto mainCam = entityVector[0];

    auto cameraComponent = scene->GetComponent<Camera>(mainCam);

    //                         index 0 -> main camera
    entt::entity selectedEntity = entityVector[0]; /// This will show up in the inspector panel

   // glfwSetKeyCallback(GLFWwindow, key_callback);
    glfwSetScrollCallback(GLFWwindow, scrollCallback);
    glfwSetMouseButtonCallback(GLFWwindow, mouseButtonCallback);
    glfwSetCursorPosCallback(GLFWwindow, mouse_callback);
    glfwSetFramebufferSizeCallback(GLFWwindow, framebuffer_size_callback);

    
    float planeVertices[] = {
        // positions            // normals         // texcoords
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
    };

    //stbi_set_flip_vertically_on_load(1);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE); 

    float viewportX = Window::s_ViewportMinX;
    float viewportY = Window::s_ViewportMinY;
    float viewportWidth = Window::s_ViewportWidth;
    float viewportHeight = Window::s_ViewportHeight;

    int windowWidth = Window::s_WindowWidth;
    int windowHeight = Window::s_WindowHeight;

    float total_percent_imgui_width  = 0.0f;
    float total_percent_imgui_height = 0.0f;

    float total_percent_imgui_start_X_affect  = 0.0f;
    float total_percent_imgui_start_Y_affect  = 0.0f;

    //Shader setup
    // Basic & Essential shader for rendering with position and color settings
    Shader shader("src/Renderer/Shader/shadow_mapping.glsl");

    Shader skyboxShader("src/Renderer/Shader/skybox.glsl");
    
    Shader LightingShader("src/Renderer/Shader/Blinn-Phong.glsl");
    Shader LightCubeShader("src/Renderer/Shader/LightCube.glsl");

    Shader simpleDepthShader("src/Renderer/Shader/shadow_mapping_depth.glsl");
    Shader debugDepthQuad("src/Renderer/Shader/debug_quad.glsl");

    debugDepthQuad.Bind();
    debugDepthQuad.setUniformInteger("depthMap", 0);
    
    glm::mat4 rotationMatrix(1);
    glm::mat4 scaleMatrix(1);
    glm::mat4 translationMatrix(1);
    glm::mat4 modelMatrix(1);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    float angle = 0.0f;
    float scaleRatio = 1.0f;
    float translation = 0.0f;


    glm::mat4 combinedMatrix(1);

    //lighting setup

    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

    

    ImGuiIO& io = ImGui::GetIO();

    // plane VAO
    unsigned int planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    

    /// Texture setup    

    unsigned int diffuseMap = loadTexture("Assets/container2.png");
    unsigned int specularMap = loadTexture("Assets/container2_specular.png");
    unsigned int lightCubeTexture = loadTexture("Assets/redstone_lamp1.jpg");
    unsigned int woodTexture = loadTexture("Assets/wood.png");
    

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shader.Bind();
    shader.setUniformInteger("diffuseTexture", 0);
    shader.setUniformInteger("shadowMap", 1);
    debugDepthQuad.Bind();
    debugDepthQuad.setUniformInteger("depthMap", 0);

    float inspector_size = 0.2f;
    total_percent_imgui_width += inspector_size;

    float hierarchy_size = 0.2f;
    total_percent_imgui_start_X_affect += hierarchy_size;
    total_percent_imgui_width += hierarchy_size;


    auto entity0 = scene->CreateEntity();
    auto entity1 = scene->CreateEntity();
    auto entity2 = scene->CreateEntity();





    while (!glfwWindowShouldClose(GLFWwindow))
    {

        cameraComponent->cameraFront = cameraFront;
        
        cameraComponent->fov = fov;

        auto cameraTransform = scene->GetComponent<Transform>(mainCam);

        cameraTransform->rotation = {pitch, roll, yaw};


        cameraPosition = cameraTransform->position;

        Window::s_Red = cameraComponent->clearColor.r;
        Window::s_Green = cameraComponent->clearColor.g;
        Window::s_Blue = cameraComponent->clearColor.b;
        Window::s_Alpha = cameraComponent->clearColor.a;

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        windowWidth = Window::s_WindowWidth;
        windowHeight = Window::s_WindowHeight;

        Window::s_ViewportWidth  = windowWidth  - windowWidth  * total_percent_imgui_width;
        Window::s_ViewportHeight = windowHeight - windowHeight * total_percent_imgui_height;

        Window::s_ViewportMinX  = windowWidth  * total_percent_imgui_start_X_affect;
        Window::s_ViewportMinY  = windowHeight * total_percent_imgui_start_Y_affect;

        viewportWidth = Window::s_ViewportWidth;
        viewportHeight = Window::s_ViewportHeight;

        viewportX = Window::s_ViewportMinX;
        viewportY = Window::s_ViewportMinY;

        processInput(GLFWwindow);

        m_Window.ImGuiNewFrame();

        viewMatrix        = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        projectionMatrix  = glm::perspective(glm::radians(fov), viewportWidth / viewportHeight, 1.0f, 100.0f);

        rotationMatrix    = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0, 0, 1));

        scaleMatrix       = glm::scale(glm::mat4(1), glm::vec3(scaleRatio));
        translationMatrix = glm::translate(glm::mat4(1), glm::vec3(translation));
        modelMatrix       = translationMatrix * rotationMatrix * scaleMatrix;        


            // IMGUI

            /// Inspector Panel

            

            ImGui::SetNextWindowPos(ImVec2(windowWidth * 0.80f, 0), ImGuiCond_Always); // Adjust the position of the inspector panel
            ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.20f, windowHeight), ImGuiCond_Always); // Set the size of the inspector panel

            ImGui::Begin("Inspector Panel", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

                auto entityProperties = scene->GetComponent<EntityProperties>(selectedEntity);
                auto transform = scene->GetComponent<Transform>(selectedEntity);

                // Checkbox for isActive
                static bool isActive = entityProperties->isActive; // Initialize from entityProperties
                ImGui::Checkbox("isActive", &isActive);
                entityProperties->isActive = isActive; // Update entityProperties

                ImGui::SameLine(); // Put the next item on the same line

                // Text field for name
                std::string name = entityProperties->name; // Initialize from entityProperties
                char nameBuffer[256];
                strcpy(nameBuffer, name.c_str()); // Convert std::string to char array
                ImGui::InputText("Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
                name = nameBuffer; // Update name in std::string format
                entityProperties->name = name; // Update entityProperties

                // Draw a horizontal line
                ImGui::Separator();

                // Transform Component using Entt
                // Assuming you have some way to get the transform component from Entt
                // Here, I'm just showing placeholder values
                ImGui::Text("Transform Component");

                // Display and modify position
                // Display and modify position
                float position[3] = { transform->position.x, transform->position.y, transform->position.z };
                ImGui::DragFloat3("Position", position, 1.0f);
                transform->position.x = position[0];
                transform->position.y = position[1];
                transform->position.z = position[2];

                // Display and modify rotation
                float rotation[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
                ImGui::DragFloat3("Rotation", rotation, 1.0f, 0.0f, 360.0f);
                transform->rotation.x = rotation[0];
                transform->rotation.y = rotation[1];
                transform->rotation.z = rotation[2];

                // Display and modify scale
                float scale[3] = { transform->scale.x, transform->scale.y, transform->scale.z };
                ImGui::DragFloat3("Scale", scale, 1.0f);
                transform->scale.x = scale[0];
                transform->scale.y = scale[1];
                transform->scale.z = scale[2];

                ImGui::Separator();

                if(!entityProperties->name.compare("Main Camera"))
                    DrawCameraInspector(*cameraComponent);
                        
            
            ImGui::End();

        /*
            // Set up ImGui layout for the folders window at the bottom
            total_percent_imgui_area_height +=

            ImGui::SetNextWindowPos(ImVec2(0, g_height * 0.75f), ImGuiCond_Always); // Adjust the position of the folders window
            ImGui::SetNextWindowSize(ImVec2(g_width, g_height * 0.25f), ImGuiCond_Always); // Set the size of the folders window

            // Begin ImGui window for the folders window
            ImGui::Begin("Folders", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            // Add ImGui content for folders window

            // End ImGui window for the folders window
            ImGui::End();
        */
            /// Hierarchy panel


            
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always); // Adjust the position of the inspector panel
            ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.20f, windowHeight * 0.8f), ImGuiCond_Always); // Set the size of the inspector panel

            ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);       
            ImGui::Separator();

                for(auto entity : entityVector){
                    EntityProperties* eP = scene->GetComponent<EntityProperties>(entity);
                    
                    if (ImGui::Button(eP->name.c_str())) {
                        selectedEntity = entity;
                    }

                }
            
            ImGui::End();


            // Engine information
            ImGui::SetNextWindowPos(ImVec2(0, windowHeight * 0.8f), ImGuiCond_Always); // Adjust the position of the inspector panel
            ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.20f, windowHeight * 0.2f), ImGuiCond_Always); // Set the size of the inspector panel

            ImGui::Begin("Engine Information", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);       
            ImGui::Separator();

                ImGui::Text("Camera position: %.2f, %.2f, %.2f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
                ImGui::Text("Viewport X = %.2f & Width = %.2f", viewportX, viewportWidth);
                ImGui::Text("Viewport Y = %.2f & Height = %.2f", viewportY, viewportHeight);
                ImGui::Text("Window Width = %d & Height = %d", windowWidth, windowHeight);
                ImGui::Text("Aspect ratio = %f / %f", viewportWidth, viewportHeight);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            
            ImGui::End();
            
        // IMGUI

    
        
        /// Draw the cube

        

     
        
           // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        simpleDepthShader.Bind();
        simpleDepthShader.setMat4("lightSpaceMatrix", &lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, woodTexture);
            renderScene(simpleDepthShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Set viewport & Clear the screen

        
        
        m_Window.ClearScreen();



        // 2. render scene as normal using the generated depth/shadow map  
        // --------------------------------------------------------------
        shader.Bind();
        shader.setMat4("projection", &projectionMatrix);
        shader.setMat4("view", &viewMatrix);
        // set light uniforms
        shader.setVec3("viewPos", cameraPosition);
        shader.setVec3("lightPos", lightPos);
        shader.setMat4("lightSpaceMatrix", &lightSpaceMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        renderScene(shader);

        // render Depth map to quad for visual debugging
        // ---------------------------------------------
        debugDepthQuad.Bind();
        debugDepthQuad.setUniformFloat("near_plane", near_plane);
        debugDepthQuad.setUniformFloat("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        //renderQuad();
        
        m_Window.ImGuiRender();


        m_Window.SwapBuffers();

    } 
    m_Window.Cleanup();
}