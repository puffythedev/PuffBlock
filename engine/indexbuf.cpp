#include "indexbuf.hpp"
#include <glad/gl.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    m_count = count;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_bufferID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Initialize(const unsigned int* data, unsigned int count){
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    m_count = count;
}