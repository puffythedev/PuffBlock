#pragma once

#include <vertexarray.hpp>
#include <vertexlayout.hpp>
#include <indexbuf.hpp>
#include <renderer.hpp>
#include <shaders.hpp>

class Holder {
    public:
        VertexArray va;
        VertexLayout layout;
        VertexBuffer vbo;
        IndexBuffer ibo;
        Holder();
        void GenerateSelf();
        void Draw(const Puffy::Engine::Renderer& renderer, Puffy::Engine::Shader& shader);
};