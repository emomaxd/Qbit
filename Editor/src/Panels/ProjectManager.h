#pragma once

#include <imgui/imgui.h>
#include <string>
#include <functional>

namespace Qbit {
    class ProjectManager {
    public:
        ProjectManager()
            : m_ShowProjectManagerWindow(true) {}

        void OnImGuiRender();

        bool IsProjectSelected() { return m_ProjectSelected; }

        void SetProjectSelected() { m_ProjectSelected = true; }

        using ProjectCallback = std::function<void(const std::string&)>;

        void SetOpenProjectCallback(const ProjectCallback& callback) { m_OpenProjectCallback = callback; }
        void SetCreateProjectCallback(const ProjectCallback& callback) { m_CreateProjectCallback = callback; }

    private:
        bool m_ProjectSelected = false;
        bool m_ShowProjectManagerWindow;
        ProjectCallback m_OpenProjectCallback;
        ProjectCallback m_CreateProjectCallback;
    };

}