#include "Holder.hpp"

Holder::Holder(){
    layout.Push<float>(3);
    layout.Push<float>(2);
}

void Holder::Draw(const Puffy::Engine::Renderer& renderer, Puffy::Engine::Shader& shader){
    Render3D(renderer.Draw(va, ibo, shader));
}

void Holder::GenerateSelf(){
    va.addBuffer(vbo, layout);
}