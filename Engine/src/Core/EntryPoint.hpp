#pragma once
#include <Qbit.h>

extern Qbit::Application* Qbit::CreateApplication(Qbit::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Qbit::Log::Init();
    QBIT_CORE_WARN("Initialized Log!");
    QBIT_WARN("Initialized Log!");

    auto app = Qbit::CreateApplication({ argc, argv });

    app->Run();

    delete app;
}