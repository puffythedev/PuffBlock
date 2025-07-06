#include "chunk.hpp"
#include <renderer.hpp>
#include <noise/FastNoiseSIMD.h>
#include <random>

FastNoiseSIMD* simd;
Chunk::Chunk(float x, float z){
    srand(1);
    position.x = x;
    position.y = z;
    simd= FastNoiseSIMD::NewFastNoiseSIMD();
    simd->SetNoiseType(FastNoiseSIMD::PerlinFractal);
    simd->SetFractalOctaves(4);
}

void Chunk::Generate(){
    float* a = simd->GetPerlinFractalSet(0, 0, 0, 16, 16, 16);
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
    vertices.clear();
    vertices.reserve(16 * 64 * 16 * 6 / 2);

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            for (int y = 0; y < 64; y++) {
                glm::vec3 blockWorldPos = {
                    static_cast<float>(x + position.x * 16),
                    static_cast<float>(y),
                    static_cast<float>(z + position.y * 16)
                };
                uint16_t blockId = blocks[x][y][z];
                if(blockId == 0) continue;

                if (!isBlockSolid(x, y, z - 1)) addFace(vertices, CubeFace::FRONT, blockWorldPos, 1);
                if (!isBlockSolid(x, y, z + 1)) addFace(vertices, CubeFace::BACK, blockWorldPos, 1);
                if (!isBlockSolid(x - 1, y, z)) addFace(vertices, CubeFace::LEFT, blockWorldPos, 1);
                if (!isBlockSolid(x + 1, y, z)) addFace(vertices, CubeFace::RIGHT, blockWorldPos, 1);
                if (!isBlockSolid(x, y + 1, z)) addFace(vertices, CubeFace::TOP, blockWorldPos, 1);
                if (!isBlockSolid(x, y - 1, z)) addFace(vertices, CubeFace::BOTTOM, blockWorldPos, 1);
            }
        }
    }

    holder.vbo.Initialize(vertices.data(), vertices.size() * sizeof(VertexNorm));
    holder.GenerateSelf();
}

bool Chunk::isBlockSolid(int x, int y, int z) {
    if (x < 0 || x >= size || z < 0 || z >= size || y < 0 || y >= 64) 
        return false;
    
    return true;
}