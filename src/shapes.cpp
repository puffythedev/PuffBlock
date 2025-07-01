#include "shapes.hpp"

std::vector<Vertex> getCubeFaceVertices(CubeFace face, const glm::vec3& offset = glm::vec3(0.0f), float size = 1.0f) {
    using glm::vec3; using glm::vec2;

    const float s = size * 0.5f;

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

    std::vector<Vertex> result(6);

    // Triangle 1
    result[0] = { corners[idx[0]] + offset, normal, uvs[0] };
    result[1] = { corners[idx[1]] + offset, normal, uvs[1] };
    result[2] = { corners[idx[2]] + offset, normal, uvs[2] };

    // Triangle 2
    result[3] = { corners[idx[2]] + offset, normal, uvs[2] };
    result[4] = { corners[idx[3]] + offset, normal, uvs[3] };
    result[5] = { corners[idx[0]] + offset, normal, uvs[0] };

    return result;
}

void addFace(std::vector<Vertex>& verts, CubeFace face, const glm::vec3& offset = glm::vec3(0.0f), float size = 1.0f) {
    using glm::vec3; using glm::vec2;

    const float s = size * 0.5f;

    vec3 corners[8] = {
        vec3(-s, -s, -s), vec3(s, -s, -s),
        vec3(s,  s, -s), vec3(-s,  s, -s),
        vec3(-s, -s,  s), vec3(s, -s,  s),
        vec3(s,  s,  s), vec3(-s,  s,  s)
    };

    static const int faceIndices[6][4] = {
        {4, 5, 6, 7},
        {1, 0, 3, 2},
        {0, 4, 7, 3},
        {5, 1, 2, 6},
        {3, 7, 6, 2},
        {0, 1, 5, 4} 
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

    verts.push_back({ corners[idx[0]] + offset, normal, uvs[0] });
    verts.push_back({ corners[idx[1]] + offset, normal, uvs[1] });
    verts.push_back({ corners[idx[2]] + offset, normal, uvs[2] });

    verts.push_back({ corners[idx[2]] + offset, normal, uvs[2] });
    verts.push_back({ corners[idx[3]] + offset, normal, uvs[3] });
    verts.push_back({ corners[idx[0]] + offset, normal, uvs[0] });
}