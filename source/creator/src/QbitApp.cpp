#include <qbit.h>
#include <entry_point.h>

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
		spec.Name = "Qbit";
		spec.CommandLineArgs = args;

		return new QbitEditor(spec);
	}

}