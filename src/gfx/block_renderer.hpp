#pragma once

#include "shader.hpp"

struct ChunkRenderer {
    Shader *shader;
    void render(Chunk &chunk);
}