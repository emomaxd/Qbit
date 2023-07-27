#include "../include/Renderer.hpp"
#include "../include/Sphere.hpp"

void Renderer::init(){
    
    InitWindow(WIDTH, HEIGHT, "Physic Engine");
    SetTargetFPS(TARGET_FPS);
    
}

void Renderer::render(){
    
    const std::vector<std::unique_ptr<Object>>& v = scene->getObjects();
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        for(auto& s : v)
            DrawCircle(s.get()->getPosition().getX(), s.get()->getPosition().getY(), dynamic_cast<Sphere*>(s.get())->getRadius(), RED);   
                 

    EndDrawing();

}
