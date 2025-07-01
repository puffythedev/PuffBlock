#pragma once
#include "shapes.hpp"

#include <vertexlayout.hpp>
#include <shaders.hpp>
#include <texsys.hpp>
#include <renderer.hpp>
#include <vertexbuf.hpp>
#include <indexbuf.hpp>
#include <vertexarray.hpp>
#include <window.hpp>

#include <glm/glm.hpp>

using namespace Puffy;

class Chunk {
    Chunk(int x, int z);

    void Generate();
    void BuildMesh();
private:
    bool isBlockSolid(int x, int y, int z);
    
    unsigned char size = 16; // 1 byte
    uint8_t blocks[16][64][16] = { 0 }; // 128KB
    glm::vec2 position; // 16 bytes
    std::vector<Vertex> vertices; // variable
};
