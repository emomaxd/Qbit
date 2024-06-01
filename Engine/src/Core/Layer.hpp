
/*
/// This class has been copied from The Cherno's Github Page
/// https://github.com/TheCherno/OpenGL
*/

#pragma once

#include <string>

#include "Timestep.hpp"


namespace Qbit {

    class Layer
    {
    public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer() = default;

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(Timestep ts) {}
            virtual void OnImGuiRender() {}
            //virtual void OnEvent(Event& event) {}

            inline const std::string& GetName() const { return m_DebugName; }
    protected:
		    std::string m_DebugName;
    };

}
