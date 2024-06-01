#include <Core/Layer.hpp>
#include <Core/EntryPoint.h>

class Sandbox : public EMax3D::Application
{
public:
    Sandbox(const EMax3D::ApplicationSpecification& specification)
        : EMax3D::Application(specification)
    {
        PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() = default;
};

EMax3D::Application* EMax3D::CreateApplication(EMax3D::ApplicationCommandLineArgs args)
{
    EMax3D::ApplicationSpecification spec;
    spec.Name = "Sandbox";
    spec.WorkingDirectory = "../Editor";
    spec.CommandLineArgs = args;

    return new Sandbox(spec);
}
