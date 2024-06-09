#include <Qbit.h>
#include "ExampleLayer.h"
#include "Qbit/Core/EntryPoint.h"

class Sandbox : public Qbit::Application
{
public:
    Sandbox(const Qbit::ApplicationSpecification& specification)
        : Qbit::Application(specification)
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() = default;
};

Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args)
{
    Qbit::ApplicationSpecification spec;
    spec.Name = "Sandbox";
    spec.WorkingDirectory = "../Editor";
    spec.CommandLineArgs = args;

    return new Sandbox(spec);
}
