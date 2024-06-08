#include <Qbit.h>
#include <Qbit/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Qbit {

	class QbitEditor : public Application
	{
	public:
		QbitEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Qbit Editor";
		spec.CommandLineArgs = args;

		return new QbitEditor(spec);
	}

}