#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

enum class CubeFace {
    FRONT,   // +Z
    BACK,    // -Z
    LEFT,    // -X
    RIGHT,   // +X
    TOP,     // +Y
    BOTTOM   // -Y
};

static inline Vertex cubeVertices[] = {
    Vertex {
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)
    },
    Vertex {
        glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(0.0f, 1.0f),
    },

    Vertex {
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f),
    },
    Vertex {
        glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f),
    },

    Vertex {
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
    },
    Vertex {
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f),
    },

    Vertex {
        glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f),
    },

    Vertex {
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f),  glm::vec2(0.0f, 0.0f),
    },

    Vertex {
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f,  1.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec3(0.0f,  1.0f, 0.0f),  glm::vec2(1.0f, 1.0f),
    },
    Vertex {
        glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec3(0.0f,  1.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    },
    Vertex {
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f,  1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)
    },
};

static inline unsigned int cubeIndices[] = {
   0, 1, 2, 2, 3, 0,        // Back
    4, 6, 5, 5, 7, 4,       // Front
    8, 10, 9, 9, 11, 8,     // Left
    12, 13, 14, 14, 15, 12, // Right
    16, 18, 17, 17, 19, 16, // Bottom
    20, 21, 22, 22, 23, 20  // Top
};
std::vector<Vertex> getCubeFaceVertices(CubeFace face, const glm::vec3& offset, float size);
void addFace(std::vector<Vertex>& verts, CubeFace face, const glm::vec3& offset, float size);