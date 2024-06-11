#pragma once

#include "Qbit.h"

class Sandbox2D : public Qbit::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Qbit::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Qbit::Event& e) override;
private:
	Qbit::OrthographicCameraController m_CameraController;

	// Temp
	Qbit::Ref<Qbit::VertexArray> m_SquareVA;
	Qbit::Ref<Qbit::Shader> m_FlatColorShader;

	Qbit::Ref<Qbit::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

