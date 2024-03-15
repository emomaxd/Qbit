#pragma once

#include "../Scene/Scene.hpp"
#include "../Renderer/Renderer.hpp"
#include "../System/Physic.hpp"
#include "../Renderer/Window.hpp"

#include <vector>

class Engine{

public:
    Engine();
    Engine(Renderer* renderer, Scene* initialScene);
    ~Engine();

    void start();
    static inline Scene* GetActiveScene(){ return s_ActiveScene; }
    inline Scene* GetScene(int index){ return m_Scenes[index]; }
    Scene* GetScene(const std::string& name);
    void AddScene(Scene* scene){ m_Scenes.push_back(scene); }

private:
    Window m_Window;
    Renderer* m_Renderer;
    std::vector<Scene*> m_Scenes;
    inline static Scene* s_ActiveScene{nullptr};

    System::Physic m_PhysicSystem;
};