#pragma once

class IndexBuffer {
public:
    IndexBuffer() {}
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    void Initialize(const unsigned int* data, unsigned int count);
    void bind() const;
    void unbind() const;
    unsigned int getCount() const { return m_count; }
private:
    unsigned int m_bufferID;
    unsigned int m_count;
};