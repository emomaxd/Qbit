#include "qbpch.h"
#include "ContentBrowserPanel.h"

#include "Qbit/Project/Project.h"
#include "Qbit/Core/Application.h"

#include <imgui/imgui.h>

#include <shellapi.h>

namespace Qbit {

    ContentBrowserPanel::ContentBrowserPanel()
        : m_BaseDirectory(Project::GetAssetDirectory()), m_CurrentDirectory(m_BaseDirectory)
    {
        m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DirectoryIcon.png");
        m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FileIcon.png");
    }

    static float padding = 16.0f;
    static float thumbnailSize = 128.0f;

#pragma region Util
    bool ContentBrowserPanel::IsTextureFile(const std::string& filepath)
    {
        std::string extension = filepath.substr(filepath.find_last_of('.') + 1);
        return (extension == "png" || extension == "jpg" || extension == "jpeg");
    }

    Ref<Texture2D> ContentBrowserPanel::LoadTexture(const std::string& filepath)
    {
        return Texture2D::Create(filepath);
    }

    Ref<Texture2D> ContentBrowserPanel::GetTextureForFile(const std::string& filepath)
    {
        if (m_TextureCache.find(filepath) != m_TextureCache.end())
        {
            return m_TextureCache[filepath];
        }

        Ref<Texture2D> texture = LoadTexture(filepath);
        m_TextureCache[filepath] = texture;
        return texture;
    }
#pragma endregion

#pragma region Context
    void ContentBrowserPanel::CreateCSharpFile(std::ofstream& file, const std::string & namespaceName, const std::string& className)
    {
        if (!file.is_open()) {
            std::cerr << "Error: Could not create file." << std::endl;
            return;
        }

        file << "using System;\n";
        file << "using Qbit;\n\n";
        file << "namespace " << namespaceName << "\n{\n";
        file << "    class " << className << ": Entity\n{\n";
        file << "        public void OnCreate()\n        {\n";
        file << "            Console.WriteLine(\"OnCreate runs once when the game has started!\");\n        }\n\n";
        file << "        public void OnUpdate(float ts)\n        {\n";
        file << "            Console.WriteLine(\"OnUpdate runs in each frame.\");\n }\n";
        file << "    }\n}\n";

        file.close();
    }

    void ContentBrowserPanel::CreateCustomFile(const std::filesystem::path& path)
    {
        // Check if the file already exists
        auto fullPath = this->m_CurrentDirectory / path;
        if (std::filesystem::exists(fullPath)) {
            std::cerr << "Error: File already exists: " << fullPath << std::endl;
            return;
        }

        // Try to create the file
        std::ofstream file(fullPath); // Open a file stream
        if (!file) {
            std::cerr << "Error: Unable to create file: " << fullPath << std::endl;
            return;
        }

        std::cout << "File created successfully: " << fullPath << std::endl;
        if (fullPath.extension() == ".cs") {
            CreateCSharpFile(file, Project::GetActive()->GetConfig().Name, path.stem().string());
        }
    }

    void ContentBrowserPanel::DisplayFileCreationPopup() {
        static char filenameBuffer[64] = ""; // Static to retain value across frames

        if (ImGui::BeginPopup("FileCreationPopup"))
        {
            ImGui::Text("Enter filename:");
            ImGui::InputText("##filename", filenameBuffer, sizeof(filenameBuffer));

            if (ImGui::Button("Create")) {
                std::string filenameInput = filenameBuffer;
                if (!filenameInput.empty()) {
                    CreateCustomFile(filenameInput);
                    std::memset(filenameBuffer, 0, sizeof(filenameBuffer)); // Clear the buffer
                    ImGui::CloseCurrentPopup();
                }
                else {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Filename cannot be empty.");
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup(); // Close the popup
            }
            ImGui::EndPopup();
        }
    }

    void ContentBrowserPanel::ShowContextMenu()
    {
        static char filenameBuffer[64] = ""; // Static to retain value across frames
        static bool fileCreationPopupOpen = false; // State variable for the file creation popup

        // Check if the right mouse button is clicked
        if (ImGui::IsMouseReleased(1) && ImGui::IsWindowHovered()) // 1 corresponds to the right mouse button
        {
            ImGui::OpenPopup("ContextMenu"); // Open the context menu
        }

        // Create a popup context menu
        if (ImGui::BeginPopup("ContextMenu")) {
            // Add menu items
            if (ImGui::MenuItem("Create File")) {
                fileCreationPopupOpen = true; // Open the file creation popup
                ImGui::CloseCurrentPopup(); // Close the context menu
            }

            if (ImGui::MenuItem("Create Folder")) {
                QB_TRACE("create folder");
            }

            if (ImGui::MenuItem("Delete")) {
                QB_TRACE("delete");
            }

            ImGui::EndPopup(); // End the context menu
        }

        // Display the file creation popup inline
        if (fileCreationPopupOpen) {
            ImGui::OpenPopup("FileCreationPopup"); // Open the file creation popup

            if (ImGui::BeginPopup("FileCreationPopup")) {
                ImGui::Text("Enter filename:");
                ImGui::InputText("##filename", filenameBuffer, sizeof(filenameBuffer));

                if (ImGui::Button("Create")) {
                    std::string filenameInput = filenameBuffer;
                    if (!filenameInput.empty()) {
                        CreateCustomFile(filenameInput);
                        std::memset(filenameBuffer, 0, sizeof(filenameBuffer)); // Clear the buffer
                        fileCreationPopupOpen = false; // Close the popup
                        ImGui::CloseCurrentPopup(); // Close the popup
                    }
                    else {
                        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Filename cannot be empty.");
                    }
                }

                ImGui::SameLine();
                if (ImGui::Button("Cancel")) {
                    fileCreationPopupOpen = false; // Close the popup
                    ImGui::CloseCurrentPopup(); // Close the popup
                }

                ImGui::EndPopup(); // End the file creation popup
            }
        }
    }
#pragma endregion

    void ContentBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");

        m_IsHovered = ImGui::IsWindowHovered();

        ShowContextMenu();

        if (ImGui::BeginTabBar("ContentBrowserTabs"))
        {
            if (ImGui::BeginTabItem("Content Browser"))
            {
                if (m_CurrentDirectory != std::filesystem::path(m_BaseDirectory))
                {
                    if (ImGui::Button("<-"))
                    {
                        m_CurrentDirectory = m_CurrentDirectory.parent_path();
                    }
                }

                float cellSize = thumbnailSize + padding;

                float panelWidth = ImGui::GetContentRegionAvail().x;
                int columnCount = (int)(panelWidth / cellSize);
                if (columnCount < 1)
                    columnCount = 1;

                ImGui::Columns(columnCount, 0, false);

                for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
                {
                    const auto& path = directoryEntry.path();
                    std::string filenameString = path.filename().string();

                    ImGui::PushID(filenameString.c_str());
                    Ref<Texture2D> icon;
                    if (directoryEntry.is_directory())
                    {
                        icon = m_DirectoryIcon;
                    }
                    else if (IsTextureFile(filenameString))
                    {
                        icon = GetTextureForFile(path.string());
                    }
                    else
                    {
                        icon = m_FileIcon;
                    }

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                    ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

                    if (ImGui::BeginDragDropSource())
                    {
                        std::filesystem::path relativePath(path);
                        const wchar_t* itemPath = relativePath.c_str();
                        ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                        ImGui::EndDragDropSource();
                    }

                    ImGui::PopStyleColor();
                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        if (directoryEntry.is_directory())
                            m_CurrentDirectory /= path.filename();

                        auto str = path.extension();
                        if (str.string()._Equal(".cs"))
                        {
                            /* !!!IMPORTANT: Make sure user has Visual Studio */
                            std::string projectName = Project::GetActive()->GetConfig().Name;
                            std::string devenvPath = "\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe\"";

                            // Construct the full path to the solution file and the command to open the specific file
                            std::string solutionPath = projectName + ".sln";
                            std::string filePath = "Assets\\Scripts\\" + filenameString;
                            std::string parameter = "/Command \"File.OpenFile Assets\\Scripts\\" + filenameString + "\"";

                            // Launch Visual Studio using ShellExecute (non-blocking)
                            ShellExecuteA(
                                NULL,                          // Handle to parent window (NULL means no specific window)
                                "open",                        // Operation to perform (open a program)
                                devenvPath.c_str(),            // Path to Visual Studio executable
                                (solutionPath + " " + parameter).c_str(),  // Solution file + parameters
                                (std::filesystem::current_path() / projectName).string().c_str(),      // Set working directory
                                SW_SHOWDEFAULT                 // How to display the window (default behavior)
                            );
                        }
                    }
                    ImGui::TextWrapped(filenameString.c_str());

                    ImGui::NextColumn();

                    ImGui::PopID();
                }

                ImGui::Columns(1);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Settings"))
            {
                ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
                ImGui::SliderFloat("Padding", &padding, 0, 32);

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }

}
