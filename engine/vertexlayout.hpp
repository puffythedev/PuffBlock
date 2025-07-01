#pragma once
#include <vector>
#include <cinttypes>
#include <glad/gl.h>

class VertexLayout {
public:
    struct Element {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;
    };
    VertexLayout() : m_stride(0) {}

    template<typename T>
    void Push(unsigned int count) {
        static_assert(false);
    }
    
    template<>
    void Push<float>(unsigned int count) {
        m_elements.push_back(Element { GL_FLOAT, count, GL_FALSE });
        m_stride += sizeof(GLfloat) * count;
    }
    
    template<>
    void Push<unsigned int>(unsigned int count) {
        m_elements.push_back(Element { GL_UNSIGNED_INT, count, GL_FALSE });
        m_stride += sizeof(GLuint) * count;
    }
    
    template<>
    void Push<unsigned char>(unsigned int count) {
        m_elements.push_back(Element { GL_UNSIGNED_BYTE, count, GL_FALSE });
        m_stride += sizeof(GLubyte) * count;
    }

    inline unsigned int getStride() const { return m_stride; }
    inline const std::vector<Element> getElements() const { return m_elements; }

private:
    unsigned int m_stride;
    std::vector<Element> m_elements;
};