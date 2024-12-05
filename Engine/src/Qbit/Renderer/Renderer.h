#pragma once

#include "Qbit/Renderer/RenderCommand.h"

#include "Qbit/Renderer/OrthographicCamera.h"
#include "Qbit/Renderer/Shader.h"
#include "Qbit/Renderer/VertexArray.h"
#include "Qbit/Renderer/RendererAPI.h"

namespace Qbit {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static Ref<ShaderLibrary> GetShaderLibrary() { return s_ShaderLibrary; }

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
		static Ref<ShaderLibrary> s_ShaderLibrary;
	};
}