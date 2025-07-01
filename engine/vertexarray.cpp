#include "vertexarray.hpp"
#include <string>

unsigned int getSizeOfType(unsigned int type){
    switch (type) {
        case GL_FLOAT: return 8;    
        case GL_UNSIGNED_INT: return 4;    
        case GL_UNSIGNED_BYTE: return 1;
    }
    // assert(false);
    return 0;
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_buffer);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_buffer);
}

void VertexArray::bind() const {
    glBindVertexArray(m_buffer);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexLayout &layout) {
    this->bind();
    vb.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(int i = 0; i < elements.size(); i++){
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (void*)offset);
        offset += elements[i].count * getSizeOfType(elements[i].type);
    }
}
