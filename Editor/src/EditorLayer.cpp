#include "EditorLayer.h"

#include <imgui/imgui.h>

namespace Qbit {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1600.0f / 900.0f)
	{
	}


	void EditorLayer::OnAttach()
	{
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.8f });
		RenderCommand::Clear();

	}

	void EditorLayer::OnImGuiRender()
	{
		ImGui::Begin("Viewport");

		// Render your game's graphics here
		//ImGui::Image((void*)yourTextureID, ImVec2(textureWidth, textureHeight));

		ImGui::End();
	}


	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
		if (m_SceneState == SceneState::Edit)
		{
			m_EditorCamera.OnEvent(e);
		}

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(QB_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(QB_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		return false;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

	void EditorLayer::OnOverlayRender()
	{
	}

	void EditorLayer::NewProject()
	{
	}

	bool EditorLayer::OpenProject()
	{
		return false;
	}

	void EditorLayer::OpenProject(const std::filesystem::path& path)
	{
	}

	void EditorLayer::SaveProject()
	{
	}

	void EditorLayer::NewScene()
	{
	}

	void EditorLayer::OpenScene()
	{
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
	}

	void EditorLayer::SaveScene()
	{
	}

	void EditorLayer::SaveSceneAs()
	{
	}

	void EditorLayer::OnScenePlay()
	{
	}

	void EditorLayer::OnSceneSimulate()
	{
	}

	void EditorLayer::OnSceneStop()
	{
	}

	void EditorLayer::OnScenePause()
	{
	}

	void EditorLayer::OnDuplicateEntity()
	{
	}

	void EditorLayer::UI_Toolbar()
	{
	}

} // namespace Qbit
