#include "chunk.hpp"

void Chunk::add_face_to_mesh(CubeFace cf, Block& block) {
    auto texture_offset = Grass().texture_offset(cf.face);

    auto face_direction = DIRECTIONS[cf.ID];

    int nx = block.position.x + face_direction.x;
    int ny = block.position.y + face_direction.y;
    int nz = block.position.z + face_direction.z;

    if (nx >= 0 && ny >= 0 && nz >= 0 && nx < this->size && ny < this->size &&
        nz < this->size && this->blocks[nx][ny][nz].isBlock == 1) {
        return;
    }

    float minTX =
        this->textureAtlas.tW * texture_offset.x / this->textureAtlas.atlasW;

    float maxTX = this->textureAtlas.tW * (texture_offset.x + 1) /
                  this->textureAtlas.atlasW;

    float minTY =
        this->textureAtlas.tH * texture_offset.y / this->textureAtlas.atlasH;

    float maxTY = this->textureAtlas.tH * (texture_offset.y + 1) /
                  this->textureAtlas.atlasH;

    glm::vec3* V = cf.vertices();

    std::vector<Vertex> tmpVertices{
        {V[0] * cf.position + block.position, glm::vec2(minTX, minTY)},
        {V[1] * cf.position + block.position, glm::vec2(maxTX, minTY)},
        {V[2] * cf.position + block.position, glm::vec2(minTX, maxTY)},
        {V[3] * cf.position + block.position, glm::vec2(maxTX, maxTY)}};

    this->vertices.push_back(tmpVertices);

    this->indices.push_back(QUAD_FACE_INDICES[cf.ID]);
}

void Chunk::prepare_block(Grass element, Block& block) {
    for (const auto& cube_face : CUBE_FACES) {
        this->add_face_to_mesh(cube_face, block);
    }
}

void Chunk::render() {
    this->mesh->draw(this->shader, this->position * (float)this->size);
}

void Chunk::init() {
    this->blocks.resize(this->size);
    for (int i = 0; i < this->size; i++) this->blocks[i].resize(this->size);

    for (int x = 0; x < this->size; x++) {
        for (int y = 0; y < this->size; y++) {
            for (int z = 0; z < this->size; z++) {
                this->blocks[x][y].push_back(
                    (struct Block){1, glm::vec3(x, y, z)});
            }
        }
    }

    for (int x = 0; x < this->size; x++) {
        for (int y = 0; y < this->size; y++) {
            for (int z = 0; z < this->size; z++) {
                this->prepare_block(Grass(), this->blocks[x][y][z]);
            }
        }
    }

    this->mesh = new Mesh(this->vertices, this->indices);
}
