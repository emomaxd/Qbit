#pragma once

#include "Scene.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include <vector>

class Engine{

public:
    Engine(){
        inputHandler = nullptr;
        renderer = nullptr;
        activeScene = nullptr;
    }
    Engine(Renderer* renderer, Scene* initialScene){
        
        this->inputHandler=InputHandler::getInstance();
        
        this->activeScene=initialScene;
        scenes.push_back(initialScene);

        this->renderer = renderer;
        
    }

    void start();
    static inline Scene* getActiveScene(){return activeScene;}
    inline Scene* getScene(int index){return scenes[index];}
    inline void addScene(Scene* scene){scenes.push_back(scene);}

private:
    Renderer* renderer;
    std::vector<Scene*> scenes;
    static Scene* activeScene;  ///
    InputHandler* inputHandler;

};