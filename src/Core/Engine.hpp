#pragma once

#include "../Scene/Scene.hpp"
#include "../Renderer/Renderer.hpp"
#include "../System/Physic.hpp"
#include "Window.hpp"

#include <vector>

class Engine{

public:
    Engine() = default;
    Engine(Renderer* renderer, Scene* initialScene);
    ~Engine();

    void start();
    static inline Scene* getActiveScene(){ return activeScene; }
    inline Scene* getScene(int index){ return scenes[index]; }
    Scene* getScene(const std::string& name);
    void addScene(Scene* scene){ scenes.push_back(scene); }

private:
    Window window;
    Renderer* renderer;
    std::vector<Scene*> scenes;
    inline static Scene* activeScene{nullptr};  ///

    System::Physic physicSystem;
};