#pragma once

#include "Qbit.h"

class ExampleLayer : public Qbit::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Qbit::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Qbit::Event& e) override;
private:
	Qbit::ShaderLibrary m_ShaderLibrary;
	Qbit::Ref<Qbit::Shader> m_Shader;
	Qbit::Ref<Qbit::VertexArray> m_VertexArray;

	Qbit::Ref<Qbit::Shader> m_FlatColorShader;
	Qbit::Ref<Qbit::VertexArray> m_SquareVA;

	Qbit::Ref<Qbit::Shader> m_TextureShader;

	Qbit::Ref<Qbit::Texture2D> m_Texture, m_ChernoLogoTexture;

	Qbit::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
