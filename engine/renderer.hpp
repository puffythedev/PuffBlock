#pragma once
#include "vertexarray.hpp"
#include "indexbuf.hpp"
#include "shaders.hpp"

inline int drawCalls = 0;
unsigned int glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#define Render3D(x) x; glCheckError(); drawCalls++

namespace Puffy::Engine {
    class Renderer {
        public:
            Renderer();
            ~Renderer();

            void Draw(const VertexArray &vao, const Shader &shader, unsigned int count) const;
            void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
            void DrawInstanced(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader, unsigned int instanceCount) const;  
	    void Clear() const;
        private:
    };
};
