#include "qbpch.h"
#include "Qbit/Renderer/Renderer2D.h"

#include "Qbit/Renderer/VertexArray.h"
#include "Qbit/Renderer/Shader.h"
#include "Qbit/Renderer/UniformBuffer.h"
#include "Qbit/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLTexture.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include "Camera.h"
#include "EditorCamera.h"


namespace Qbit {


	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> QuadShader;

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		float quadVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		s_Data.QuadVertexArray->Bind();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"     }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);


		s_Data.QuadShader = Shader::Create("assets/shaders/FlatColor.glsl");


		
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data.QuadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data.QuadShader)->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data.QuadShader)->SetMat4("u_Transform", glm::mat4(1.0f));

	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data.QuadShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data.QuadShader)->SetFloat3("u_Color", { color });

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);

		s_Data.Stats.QuadCount += 1;
		s_Data.Stats.DrawCalls += 1;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

}