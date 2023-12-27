#include "Engine.hpp"


int main(){

    /// INITIAL SCENE
    Scene* scene = new Scene();
    
    Renderer* renderer = new Renderer(scene);

    Engine engine(renderer, scene);

    engine.start();

    return 0;
}
