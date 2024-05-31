#pragma once
#include "../../Engine/src/Core/Layer.hpp"

namespace EMax3D{
    class EditorLayer : public Layer{
        EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		//void OnEvent(Event& e) override;
	private:
		//bool OnKeyPressed(KeyPressedEvent& e);
		//bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		
		void OnOverlayRender();

		void NewProject(){
            int a = 5;
        }
		bool OpenProject();
		//void OpenProject(const std::filesystem::path& path);
		void SaveProject();

		void NewScene();
		void OpenScene();
		//void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		//void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneSimulate();
		void OnSceneStop();
		void OnScenePause();

		void OnDuplicateEntity();
    };
}