#include "ExampleLayer.h"
#include "imgui/imgui.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Qbit::Timestep ts)
{
	//QB_INFO("ExampleLayer::Update");
}

void ExampleLayer::OnEvent(Qbit::Event& e)
{
	QB_TRACE("{0}", e.ToString());
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings - ExampleLayer");

	//auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	//ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	//ImGui::Text("Quads: %d", stats.QuadCount);
	//ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	//ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}