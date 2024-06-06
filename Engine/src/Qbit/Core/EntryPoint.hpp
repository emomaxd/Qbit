#pragma once
#include <Qbit.h>

extern Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Qbit::Log::Init();
    QB_CORE_WARN("Initialized Log!");
    QB_WARN("Initialized Log!");

    auto app = Qbit::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}