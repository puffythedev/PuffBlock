#define STB_IMAGE_IMPLEMENTATION
#include "texsys.hpp"
#include <glad/gl.h>
#include <iostream>
#include <algorithm>

Texture2D TextureManager::LoadTexture(const std::string& name, const std::string& filePath) {
    Texture2D texture;
    stbi_set_flip_vertically_on_load(true);

    int nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &texture.width, &texture.height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << '\n';
        return texture;
    }

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    GLenum format = GL_RGB;
    if (nrChannels == 4) format = GL_RGBA;
    else if (nrChannels == 3) format = GL_RGB;
    else if (nrChannels == 1) format = GL_RED;

    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0,
        format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    stbi_image_free(data);

    textures[name] = texture;
    return texture;
}

void TextureManager::RemoveTexture(const std::string& name) {
    if (textures.contains(name)) {
        glDeleteTextures(1, &textures[name].id);
        textures.erase(name);
    }
}

Texture2D TextureManager::GetTexture(const std::string& name) const {
    if (textures.contains(name))
        return textures.at(name);
    return {};
}

void TextureManager::Clear() {
    for (auto& [_, tex] : textures)
        glDeleteTextures(1, &tex.id);
    textures.clear();
}

void Texture2D::bind(int channel) {
    m_channel = channel;
    glActiveTexture(GL_TEXTURE0 + channel);
    glBindTexture(GL_TEXTURE_2D, id);
}
void Texture2D::unbind() const {
    glActiveTexture(GL_TEXTURE0 + m_channel);
    glBindTexture(GL_TEXTURE_2D, 0);
}