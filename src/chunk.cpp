#include "chunk.hpp"
#include <renderer.hpp>

Chunk::Chunk(int x, int z){
    position.x = x;
    position.y = z;
}

void Chunk::Generate(){
    for(unsigned char x = 0; x < size; x++){
        for(unsigned char z = 0; z < size; z++){
            int maxy = 64;

            for(unsigned char y = 0; y < maxy; y++){
                blocks[x][y][z] = 1;
            }
        }
    }
}

void Chunk::BuildMesh() {
    vertices.reserve(16 * 64 * 16 * 6 / 2);

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            for (int y = 0; y < 64; y++) {
                glm::vec3 blockWorldPos = {
                    static_cast<float>(x + position.x * 16),
                    static_cast<float>(y),
                    static_cast<float>(z + position.y * 16)
                };

                if (!isBlockSolid(x, y, z - 1)) addFace(vertices, CubeFace::FRONT, blockWorldPos, 1.0f);
                if (!isBlockSolid(x, y, z + 1)) addFace(vertices, CubeFace::BACK, blockWorldPos, 1.0f);
                if (!isBlockSolid(x - 1, y, z)) addFace(vertices, CubeFace::LEFT, blockWorldPos, 1.0f);
                if (!isBlockSolid(x + 1, y, z)) addFace(vertices, CubeFace::RIGHT, blockWorldPos, 1.0f);
                if (!isBlockSolid(x, y + 1, z)) addFace(vertices, CubeFace::TOP, blockWorldPos, 1.0f);
                if (!isBlockSolid(x, y - 1, z)) addFace(vertices, CubeFace::BOTTOM, blockWorldPos, 1.0f);
            }
        }
    }
}

bool Chunk::isBlockSolid(int x, int y, int z) {
    if (x < 0 || x >= 16 || z < 0 || z >= 16 || y < 0 || y >= 64) 
        return false;
    
    return true;
}