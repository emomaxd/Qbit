#include "ProjectManager.h"
#include "Qbit/Utils/PlatformUtils.h"

namespace Qbit {

    void ProjectManager::OnImGuiRender() {
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("Project Manager", &m_ShowProjectManagerWindow, window_flags);

        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 button_size = ImVec2(200, 50);
        float button_x = (window_size.x - button_size.x) * 0.5f;

        const char* text = "Select or Create a Project";
        ImVec2 text_size = ImGui::CalcTextSize(text);
        ImVec2 text_pos = ImVec2((window_size.x - text_size.x) * 0.5f, (window_size.y - text_size.y - button_size.y - 30.0f) * 0.5f);
        ImGui::SetCursorPos(text_pos);
        ImGui::TextUnformatted(text);

        ImGui::SetCursorPos(ImVec2(button_x, text_pos.y + text_size.y + 20.0f));
        if (ImGui::Button("Open Project", button_size)) {
            std::string filepath = FileDialogs::OpenFile("Qbit Project (*.qproj)\0*.qproj\0");
            if (!filepath.empty() && m_OpenProjectCallback) {
                m_OpenProjectCallback(filepath);
                m_ShowProjectManagerWindow = false;
            }
        }

        ImGui::SetCursorPos(ImVec2(button_x, text_pos.y + text_size.y + 20.0f + button_size.y + 10.0f));
        if (ImGui::Button("New Project", button_size)) {
            std::string filepath = FileDialogs::SaveFile("Qbit Project (*.qproj)\0*.qproj\0");
            if (!filepath.empty() && m_CreateProjectCallback) {
                m_CreateProjectCallback(filepath);
                m_ShowProjectManagerWindow = false;
            }
        }

        ImGui::End();
    }
}
