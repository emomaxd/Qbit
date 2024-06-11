#include "ExampleLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1600.0f / 900.0f)
{
	m_VertexArray = Qbit::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Qbit::Ref<Qbit::VertexBuffer> vertexBuffer = Qbit::VertexBuffer::Create(vertices, sizeof(vertices));
	Qbit::BufferLayout layout = {
		{ Qbit::ShaderDataType::Float3, "a_Position" },
		{ Qbit::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Qbit::Ref<Qbit::IndexBuffer> indexBuffer = Qbit::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Qbit::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Qbit::Ref<Qbit::VertexBuffer> squareVB = Qbit::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Qbit::ShaderDataType::Float3, "a_Position" },
		{ Qbit::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Qbit::Ref<Qbit::IndexBuffer> squareIB = Qbit::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_Shader = m_ShaderLibrary.Load("../Sandbox/assets/shaders/triangle_demo.glsl");
	m_FlatColorShader = m_ShaderLibrary.Load("../Sandbox/assets/shaders/FlatColor.glsl");
	m_TextureShader = m_ShaderLibrary.Load("../Sandbox/assets/shaders/Texture.glsl");

	m_Texture = Qbit::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Qbit::Texture2D::Create("../Sandbox/assets/textures/ChernoLogo.png");

	m_TextureShader->Bind();
	m_TextureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Qbit::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Qbit::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Qbit::RenderCommand::Clear();

	Qbit::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Qbit::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	m_TextureShader->Bind();

	m_Texture->Bind();
	Qbit::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Qbit::Renderer::Submit(m_TextureShader, m_SquareVA,
		glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Triangle
	Qbit::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -1.0f, 0.0f)));

	Qbit::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	float fps = ImGui::GetIO().Framerate;
	ImGui::Text("FPS: %.1f", fps);
	ImGui::End();
}

void ExampleLayer::OnEvent(Qbit::Event& e)
{
	m_CameraController.OnEvent(e);
}