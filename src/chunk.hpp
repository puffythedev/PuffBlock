#pragma once
#include "shapes.hpp"
#include "Holder.hpp"

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
public:
    Holder holder;
    Chunk(float x, float z);

    void Generate();
    void BuildMesh();
    std::vector<VertexNorm> vertices; // variable
private:
    bool isBlockSolid(int x, int y, int z);
    static const unsigned char size = 16; // 1 byte
    uint8_t blocks[size][64][size] = { 0 }; // 128KB
    glm::vec2 position; // 16 bytes
};
