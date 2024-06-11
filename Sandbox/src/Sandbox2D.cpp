#include "qbpch.h"
#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Qbit::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	
	// Render
	Qbit::Renderer2D::ResetStats();

	{
		Qbit::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Qbit::RenderCommand::Clear();
	}

	{


		Qbit::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Qbit::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Qbit::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);

		Qbit::Renderer2D::EndScene();

		Qbit::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Qbit::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Qbit::Renderer2D::EndScene();
	}
	
}

void Sandbox2D::OnImGuiRender()
{
	
	ImGui::Begin("Settings");

	auto stats = Qbit::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	float fps = ImGui::GetIO().Framerate;
	ImGui::Text("FPS: %.1f", fps);

	ImGui::End();
	
}

void Sandbox2D::OnEvent(Qbit::Event& e)
{
	m_CameraController.OnEvent(e);
}