#include <Qbit.h>

class Sandbox : public Qbit::Application
{
public:
    Sandbox(const Qbit::ApplicationSpecification& specification)
        : Qbit::Application(specification)
    {
        //PushLayer(new ExampleLayer());
        //PushLayer(new Sandbox2D());
    }

    ~Sandbox() = default;
};

Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args)
{
    std::cout << "Hello from sandbox!\n";
    Qbit::ApplicationSpecification spec;
    spec.Name = "Sandbox";
    spec.WorkingDirectory = "../Editor";
    spec.CommandLineArgs = args;

    return new Sandbox(spec);
}
