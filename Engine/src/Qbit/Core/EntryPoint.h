#pragma once
#include <Qbit.h>

extern Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Qbit::Log::Init();
    QB_CORE_WARN("Initialized Log!");
    QB_WARN("Initialized Log!");

    QB_PROFILE_BEGIN_SESSION("Startup", "QbitProfile-Startup.json");
    auto app = Qbit::CreateApplication({ argc, argv });
    QB_PROFILE_END_SESSION();
    
    QB_PROFILE_BEGIN_SESSION("Startup", "QbitProfile-Runtime.json");
    app->Run();
    QB_PROFILE_END_SESSION();

    QB_PROFILE_BEGIN_SESSION("Startup", "QbitProfile-Shutdown.json");
    delete app;
    QB_PROFILE_END_SESSION();
}