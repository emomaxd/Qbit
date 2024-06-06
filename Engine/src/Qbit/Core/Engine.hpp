#pragma once
/*
#include "../Scene/Scene.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Window.hpp"

#include <vector>

namespace Qbit {


class Engine{

    public:
        Engine();
        ~Engine();

        void start();

        static inline Scene* GetActiveScene(){ return s_ActiveScene; }
        inline Scene* GetScene(const std::string& name){ return m_Scenes[name]; }
        void AddScene(Scene* scene){ m_Scenes.insert({scene->GetName(), scene}); }
        
        inline static Scene* s_ActiveScene{nullptr};

    private:
        Window m_Window;
        Renderer* m_Renderer;
        std::unordered_map<std::string, Scene*> m_Scenes;
        unsigned int m_SceneCount = 0;

        
    };

}
*/