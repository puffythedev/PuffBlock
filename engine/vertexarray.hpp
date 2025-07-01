#pragma once
#include "vertexbuf.hpp"
#include "vertexlayout.hpp"

class VertexArray {
public:
    int e = 0;
    VertexArray();
    ~VertexArray();
    
    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vb, const VertexLayout& layout);
private:
    unsigned int m_buffer;
};
