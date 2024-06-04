#pragma once
#include "Engine.hpp"
#include "Application.hpp"


extern Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    //EMax3D::Log::Init();

    //PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
    auto app = Qbit::CreateApplication({ argc, argv });
    //PROFILE_END_SESSION();

    //PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
    app->Run();
    //PROFILE_END_SESSION();

    //PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
    delete app;
    //PROFILE_END_SESSION();
}