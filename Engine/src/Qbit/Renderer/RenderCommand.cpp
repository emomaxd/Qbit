#include "qbpch.h"
#include "Qbit/Renderer/RenderCommand.h"

namespace Qbit {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}