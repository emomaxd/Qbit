#include "Engine.hpp"

#include <iostream>
#include <thread>
#include <cmath>
#include "../../Dependencies/stb_image.h"
#include <random>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/random.hpp>


namespace EMax3D{

    std::vector<glm::mat4> getLightSpaceMatrices();
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

    unsigned int MSAA_LEVEL = 4;


    const glm::vec3 lightDir = glm::normalize(glm::vec3(20.0f, 50, 20.0f));
    unsigned int lightFBO;
    unsigned int lightDepthMaps;
    constexpr unsigned int depthMapResolution = 4096;
    std::vector<glm::mat4> lightMatricesCache;
    int fb_width = 1600;
    int fb_height = 900;

    bool showQuad = false;

    float cameraNearPlane = 0.1f;
    float cameraFarPlane = 100.0f;

    int debugLayer = 0;

    float yaw = -90.0f;
    float roll = 0.0f;
    float pitch = 0.0f;
    float fov = 45.0f;

    float vertical = 0.0f;
    float horizontal = 0.0f;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    std::vector<float> shadowCascadeLevels{ cameraFarPlane / 50.0f, cameraFarPlane / 25.0f, cameraFarPlane / 10.0f, cameraFarPlane / 2.0f };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {

        EMax3D::Window::s_WindowWidth = width;
        EMax3D::Window::s_WindowHeight = height;

        fb_width = width;
        fb_height = height;

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
    
    std::vector<glm::vec3> generateRandomCubeRotations(int numRotations) {
        std::vector<glm::vec3> rotations;
        rotations.reserve(numRotations); // Reserve space for better performance

        for (int i = 0; i < numRotations; ++i) {
            float x = glm::linearRand(-360.0f, 360.0f);
            float y = glm::linearRand(-360.0f, 360.0f);
            float z = glm::linearRand(-360.0f, 360.0f);

            rotations.emplace_back(x, y, z);
        }

        return rotations;
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


    
    int cubeCount = 10;

    unsigned int planeVAO;
    std::vector<glm::vec3> rPositions;
    void renderScene(Shader1 &shader)
    {

        auto& scene = Engine::s_ActiveScene;
        auto& entityV = Engine::s_ActiveScene->m_EntityVector;

       
       

        // floor
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        for (auto e : entityV) {
            glm::mat4 model1 = glm::mat4(1.0f);
            auto transformC = Engine::s_ActiveScene->GetComponent<Transform>(e);
            model1 = glm::translate(model1, transformC->position);

            model1 = glm::rotate(model1, transformC->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model1 = glm::rotate(model1, transformC->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model1 = glm::rotate(model1, transformC->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            model1 = glm::scale(model1, transformC->scale);
            shader.setMat4("model", model1);
            renderCube();
        }

        /*
        // cubes
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderCube();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderCube();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
        model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        model = glm::scale(model, glm::vec3(0.25));
        shader.setMat4("model", model);
        renderCube();
        */
    }



    void DrawCameraInspector(Camera& camera) {
        ImGui::Text("Camera");

        ImGui::Combo("Projection", reinterpret_cast<int*>(&camera.projection), "Perspective\0Orthographic\0");

        ImGui::DragFloat("Field of View", &fov, 1.0f, 1.0f, 45.0f);
        ImGui::ColorEdit4("Clear Color", glm::value_ptr(camera.clearColor));


        // Here you can add more controls for other camera properties if needed
    }

    std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& projview)
    {
        const auto inv = glm::inverse(projview);

        std::vector<glm::vec4> frustumCorners;
        for (unsigned int x = 0; x < 2; ++x)
        {
            for (unsigned int y = 0; y < 2; ++y)
            {
                for (unsigned int z = 0; z < 2; ++z)
                {
                    const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                    frustumCorners.push_back(pt / pt.w);
                }
            }
        }

        return frustumCorners;
    }


    std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& proj, const glm::mat4& view)
    {
        return getFrustumCornersWorldSpace(proj * view);
    }

    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane)
    {

        auto vievm = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        const auto proj = glm::perspective(
            glm::radians(fov), (float)fb_width / (float)fb_height, nearPlane,
            farPlane);
        const auto corners = getFrustumCornersWorldSpace(proj, vievm);

        glm::vec3 center = glm::vec3(0, 0, 0);
        for (const auto& v : corners)
        {
            center += glm::vec3(v);
        }
        center /= corners.size();

        const auto lightView = glm::lookAt(center + lightDir, center, glm::vec3(0.0f, 1.0f, 0.0f));

        float minX = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float minY = std::numeric_limits<float>::max();
        float maxY = std::numeric_limits<float>::lowest();
        float minZ = std::numeric_limits<float>::max();
        float maxZ = std::numeric_limits<float>::lowest();
        for (const auto& v : corners)
        {
            const auto trf = lightView * v;
            minX = std::min(minX, trf.x);
            maxX = std::max(maxX, trf.x);
            minY = std::min(minY, trf.y);
            maxY = std::max(maxY, trf.y);
            minZ = std::min(minZ, trf.z);
            maxZ = std::max(maxZ, trf.z);
        }

        // Tune this parameter according to the scene
        constexpr float zMult = 10.0f;
        if (minZ < 0)
        {
            minZ *= zMult;
        }
        else
        {
            minZ /= zMult;
        }
        if (maxZ < 0)
        {
            maxZ /= zMult;
        }
        else
        {
            maxZ *= zMult;
        }

        const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
        return lightProjection * lightView;
    }

    std::vector<glm::mat4> getLightSpaceMatrices()
    {
        std::vector<glm::mat4> ret;
        for (size_t i = 0; i < shadowCascadeLevels.size() + 1; ++i)
        {
            if (i == 0)
            {
                ret.push_back(getLightSpaceMatrix(cameraNearPlane, shadowCascadeLevels[i]));
            }
            else if (i < shadowCascadeLevels.size())
            {
                ret.push_back(getLightSpaceMatrix(shadowCascadeLevels[i - 1], shadowCascadeLevels[i]));
            }
            else
            {
                ret.push_back(getLightSpaceMatrix(shadowCascadeLevels[i - 1], cameraFarPlane));
            }
        }
        return ret;
    }
  

    int renderRange = 5;

    void Engine::start(){
        
        auto GLFWwindow = m_Window.GetWindow();

        rPositions = generateRandomPositions(cubeCount, -renderRange, renderRange, 0, renderRange, -renderRange, renderRange);
        auto scene = s_ActiveScene;

        auto rotations = generateRandomCubeRotations(cubeCount);

        

        for (int i = 0; i < cubeCount; ++i) {
            auto e = scene->CreateEntity();
            auto transformC = Engine::s_ActiveScene->GetComponent<Transform>(e);
            transformC->position = rPositions[i];
            transformC->rotation = rotations[i];
            transformC->scale = glm::vec3(0.5f);
        }

        

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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_LINE_SMOOTH);

        glfwWindowHint(GLFW_SAMPLES, MSAA_LEVEL);
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
        
        glm::mat4 rotationMatrix(1);
        glm::mat4 scaleMatrix(1);
        glm::mat4 translationMatrix(1);
        glm::mat4 modelMatrix(1);

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

        glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        float angle = 0.0f;
        float scaleRatio = 1.0f;
        float translation = 0.0f;


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
        unsigned int woodTexture = loadTexture("Assets/wood.png");
        

        float inspector_size = 0.2f;
        total_percent_imgui_width += inspector_size;

        float hierarchy_size = 0.2f;
        total_percent_imgui_start_X_affect += hierarchy_size;
        total_percent_imgui_width += hierarchy_size;

        const glm::vec3 lightDir = glm::normalize(glm::vec3(20.0f, 50, 20.0f));
        unsigned int lightFBO;
        unsigned int lightDepthMaps;
        constexpr unsigned int depthMapResolution = 4096;

        bool showQuad = false;

        // build and compile shaders
        // -------------------------
        Shader1 shader("src/Renderer/Shader/shadow_mapping.vs", "src/Renderer/Shader/shadow_mapping.fs");
        Shader1 simpleDepthShader("src/Renderer/Shader/shadow_mapping_depth.vs", "src/Renderer/Shader/shadow_mapping_depth.fs", "src/Renderer/Shader/shadow_mapping_depth.gs");
        Shader1 debugDepthQuad("src/Renderer/Shader/debug_quad.vs", "src/Renderer/Shader/debug_quad.fs");
        Shader1 debugCascadeShader("src/Renderer/Shader/debug_cascade.vs", "src/Renderer/Shader/debug_cascade.fs");

        // configure light FBO
        // -----------------------
        glGenFramebuffers(1, &lightFBO);

        glGenTextures(1, &lightDepthMaps);
        glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
        glTexImage3D(
        GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, depthMapResolution, depthMapResolution, int(shadowCascadeLevels.size()) + 1,
            0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        constexpr float bordercolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, bordercolor);

        glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, lightDepthMaps, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
            throw 0;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // configure UBO
        // --------------------
        unsigned int matricesUBO;
        glGenBuffers(1, &matricesUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4x4) * 16, nullptr, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, matricesUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // shader configuration
        // --------------------
        shader.use();
        shader.setInt("diffuseTexture", 0);
        shader.setInt("shadowMap", 1);
        debugDepthQuad.use();
        debugDepthQuad.setInt("depthMap", 0);


        while (!glfwWindowShouldClose(GLFWwindow))
        {

            glfwWindowHint(GLFW_SAMPLES, MSAA_LEVEL);

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

            fb_width = viewportWidth;
            fb_height = viewportHeight;

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
                    ImGui::Text("Transform Component");

                    // Display and modify position
                    float position[3] = { transform->position.x, transform->position.y, transform->position.z };
                    ImGui::DragFloat3("Position", position, 1.0f);
                    transform->position.x = position[0];
                    transform->position.y = position[1];
                    transform->position.z = position[2];

                    // Display and modify rotation
                    float rotation[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
                    ImGui::DragFloat3("Rotation", rotation, 0.1f, -360.0f, 360.0f);
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

                    if(ImGui::DragInt("Cube Count", &cubeCount, 0.5f, 1)) {
                        cubeCount = std::max(cubeCount, 0);
                        scene->DeleteAllEntities();
                        rPositions = generateRandomPositions(cubeCount, -renderRange, renderRange, 0, renderRange, -renderRange, renderRange);
                        auto rotations = generateRandomCubeRotations(cubeCount);



                        for (int i = 0; i < cubeCount; ++i) {
                            auto e = scene->CreateEntity();
                            auto transformC = Engine::s_ActiveScene->GetComponent<Transform>(e);
                            transformC->position = rPositions[i];
                            transformC->rotation = rotations[i];
                            transformC->scale = glm::vec3(0.5f);
                        }
                    }

                    if (ImGui::DragInt("Render Range", &renderRange, 0.2f, 0)) {
                        renderRange = std::max(renderRange, 0);
                        scene->DeleteAllEntities();
                        rPositions = generateRandomPositions(cubeCount, -renderRange, renderRange, 0, renderRange, -renderRange, renderRange);
                        auto rotations = generateRandomCubeRotations(cubeCount);



                        for (int i = 0; i < cubeCount; ++i) {
                            auto e = scene->CreateEntity();
                            auto transformC = Engine::s_ActiveScene->GetComponent<Transform>(e);
                            transformC->position = rPositions[i];
                            transformC->rotation = rotations[i];
                            transformC->scale = glm::vec3(0.5f);
                        }
                    }

                
                ImGui::End();
                
            // IMGUI
    
            
            /// Draw the cube

            
            // 0. UBO setup
            const auto lightMatrices = getLightSpaceMatrices();
            glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
            for (size_t i = 0; i < lightMatrices.size(); ++i)
            {
                glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4), &lightMatrices[i]);
            }
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        
            // 1. render depth of scene to texture (from light's perspective)
            // --------------------------------------------------------------
            //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
            // render scene from light's point of view
            simpleDepthShader.use();

            glBindFramebuffer(GL_FRAMEBUFFER, lightFBO);
            glViewport(0, 0, depthMapResolution, depthMapResolution);
            glClear(GL_DEPTH_BUFFER_BIT);
            glCullFace(GL_FRONT);  // peter panning
            renderScene(simpleDepthShader);
            glCullFace(GL_BACK);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // reset viewport
            //glViewport(0, 0, fb_width, fb_height);
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 2. render scene as normal using the generated depth/shadow map  
            // --------------------------------------------------------------
            //glViewport(0, 0, fb_width, fb_height);
            m_Window.ClearScreen();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.use();
            const glm::mat4 projection = glm::perspective(glm::radians(fov), (float)fb_width / (float)fb_height, cameraNearPlane, cameraFarPlane);
            const glm::mat4 view = viewMatrix;
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);
            // set light uniforms
            shader.setVec3("viewPos", cameraPosition);
            shader.setVec3("lightDir", lightDir);
            shader.setFloat("farPlane", cameraFarPlane);
            shader.setInt("cascadeCount", shadowCascadeLevels.size());
            for (size_t i = 0; i < shadowCascadeLevels.size(); ++i)
            {
                shader.setFloat("cascadePlaneDistances[" + std::to_string(i) + "]", shadowCascadeLevels[i]);
            }
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, woodTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D_ARRAY, lightDepthMaps);
            renderScene(shader);


            m_Window.ImGuiRender();


            m_Window.SwapBuffers();

        } 
        m_Window.Cleanup();
    }

}