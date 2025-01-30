#include "qbpch.h"
#include "Qbit/void/RenderCommand.h"

namespace Qbit {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}