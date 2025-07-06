#include "shapes.hpp"
#include <array>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

std::array<VertexNorm, 6> GenerateCubeFaceVertices(glm::vec3 pos, CubeFace face, uint16_t blockId) {
    if (blockId == 0) [[unlikely]] {
        spdlog::error("BlockID 0 tried to generate, exiting...\n");
        exit(57); // Error::BlockAccessInvalid
    }

    const float spriteSize = 1.0f / 16.0f;

    int texIndex = blockId - 1;

    std::array<VertexNorm, 6> vertices;

    switch(face) {
        case CubeFace::FRONT:
            vertices = {{
                {glm::vec3(-0.5f,-0.5f,-0.5f),  glm::vec2(0.0f,0.0f)},
                {glm::vec3( 0.5f,-0.5f,-0.5f),  glm::vec2(1.0f,0.0f)},
                {glm::vec3( 0.5f, 0.5f,-0.5f),  glm::vec2(1.0f,1.0f)},
                {glm::vec3( 0.5f, 0.5f,-0.5f),  glm::vec2(1.0f,1.0f)},
                {glm::vec3(-0.5f, 0.5f,-0.5f),  glm::vec2(0.0f,1.0f)},
                {glm::vec3(-0.5f,-0.5f,-0.5f),  glm::vec2(0.0f,0.0f)},
            }};
            break;

        case CubeFace::BACK:
            vertices = {{
                {pos + glm::vec3(-0.5f, -0.5f,  0.5f),  {0.0f, 0.0f}},
                {pos + glm::vec3( 0.5f, -0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3( 0.5f,  0.5f,  0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3( 0.5f,  0.5f,  0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3(-0.5f,  0.5f,  0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3(-0.5f, -0.5f,  0.5f),  {0.0f, 0.0f}},
            }};
            break;

        case CubeFace::LEFT:
            vertices = {{
                {pos + glm::vec3(-0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3(-0.5f,  0.5f, -0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3(-0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3(-0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3(-0.5f, -0.5f,  0.5f),  {0.0f, 0.0f}},
                {pos + glm::vec3(-0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
            }};
            break;

        case CubeFace::RIGHT:
            vertices = {{
                {pos + glm::vec3(0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3(0.5f,  0.5f, -0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3(0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3(0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3(0.5f, -0.5f,  0.5f),  {0.0f, 0.0f}},
                {pos + glm::vec3(0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
            }};
            break;

        case CubeFace::TOP:
            vertices = {{
                {pos + glm::vec3(-0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3( 0.5f, -0.5f, -0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3( 0.5f, -0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3( 0.5f, -0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3(-0.5f, -0.5f,  0.5f),  {0.0f, 0.0f}},
                {pos + glm::vec3(-0.5f, -0.5f, -0.5f),  {0.0f, 1.0f}},
            }};
            break;

        case CubeFace::BOTTOM:
            vertices = {{
                {pos + glm::vec3(-0.5f,  0.5f, -0.5f),  {0.0f, 1.0f}},
                {pos + glm::vec3( 0.5f,  0.5f, -0.5f),  {1.0f, 1.0f}},
                {pos + glm::vec3( 0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3( 0.5f,  0.5f,  0.5f),  {1.0f, 0.0f}},
                {pos + glm::vec3(-0.5f,  0.5f,  0.5f),  {0.0f, 0.0f}},
                {pos + glm::vec3(-0.5f,  0.5f, -0.5f),  {0.0f, 1.0f}}
            }};
            break;
    }

    return vertices;
}

std::array<VertexNorm, 6> getCubeFaceVertices(CubeFace face, const glm::vec3& offset = glm::vec3(0.0f), float size = 1.0f) {
    using glm::vec3; using glm::vec2;

    const float s = 0.5f;

    vec3 corners[8] = {
        vec3(-s, -s, -s), vec3(s, -s, -s),
        vec3(s,  s, -s), vec3(-s,  s, -s),
        vec3(-s, -s,  s), vec3(s, -s,  s),
        vec3(s,  s,  s), vec3(-s,  s,  s)
    };

    // These are quads made from indices into corners[], each representing a face
    static const int faceIndices[6][4] = {
        {4, 5, 6, 7}, // FRONT (+Z)
        {1, 0, 3, 2}, // BACK  (-Z)
        {0, 4, 7, 3}, // LEFT  (-X)
        {5, 1, 2, 6}, // RIGHT (+X)
        {3, 7, 6, 2}, // TOP   (+Y)
        {0, 1, 5, 4}  // BOTTOM(-Y)
    };

    static const vec3 normals[6] = {
        vec3(0, 0,  1), vec3(0, 0, -1),
        vec3(-1, 0, 0), vec3(1, 0, 0),
        vec3(0, 1,  0), vec3(0, -1, 0)
    };

    static const vec2 uvs[4] = {
        vec2(0, 0), vec2(1, 0),
        vec2(1, 1), vec2(0, 1)
    };

    const int* idx = faceIndices[(int)face];
    vec3 normal = normals[(int)face];

    std::array<VertexNorm, 6> result;

    // Triangle 1
    result[0] = { corners[idx[0]] + offset, uvs[0] };
    result[1] = { corners[idx[1]] + offset, uvs[1] };
    result[2] = { corners[idx[2]] + offset, uvs[2] };

    // Triangle 2
    result[3] = { corners[idx[2]] + offset, uvs[2] };
    result[4] = { corners[idx[3]] + offset, uvs[3] };
    result[5] = { corners[idx[0]] + offset, uvs[0] };

    return result;
}

void addFace(std::vector<VertexNorm>& verts, CubeFace face, const glm::vec3& offset = glm::vec3(0.0f), uint16_t size = 1) {
    auto hello = GenerateCubeFaceVertices(offset, face, size);

    verts.insert(verts.end(), hello.begin(), hello.end());
}