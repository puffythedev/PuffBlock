#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include "renderer.hpp"

std::string error;
unsigned int glCheckError_(const char* file, int line) {
    unsigned int errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        switch (errorCode) {
            case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default: error = "UNKNOWN_ERROR"; break;
        }
        spdlog::error("OpenGL Error [{}] {} | {}:{}", errorCode, error, file, line);
        assert(!errorCode);
    }
    return errorCode;
}

namespace Puffy::Engine {

    Renderer::Renderer() {
        
    }
    
    Renderer::~Renderer() {
        
    }

    void Renderer::Draw(const VertexArray &vao, const Shader &shader, unsigned int count) const {
        vao.bind();
        shader.bind();
    
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) const {
        vao.bind();
        shader.bind();
        ibo.bind();
    
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
    }

    void Renderer::DrawInstanced(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader, unsigned int instanceCount) const {
    	vao.bind();
    	shader.bind();
    	ibo.bind();
    
    	glDrawElementsInstanced(
        	GL_TRIANGLES,
        	ibo.getCount(),
        	GL_UNSIGNED_INT,
        	nullptr,
        	instanceCount
	    );
    }

    void Renderer::Clear() const {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }
}
