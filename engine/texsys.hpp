#pragma once
#include <unordered_map>
#include <string>
#include "stb_image.h"

struct Texture2D {
    unsigned int id = 0;
    int width = 0;
    int height = 0;
    void bind(int channel);
    void unbind() const;
private:
    int m_channel = 0;
};


class TextureManager {
public:
    Texture2D LoadTexture(const std::string& name, const std::string& filePath);
    void RemoveTexture(const std::string& name);
    Texture2D GetTexture(const std::string& name) const;
    void Clear();

private:
    std::unordered_map<std::string, Texture2D> textures;
};
