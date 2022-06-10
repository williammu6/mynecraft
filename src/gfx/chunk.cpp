#include "chunk.hpp"
#include "../state.hpp"

void Chunk::prepare_face(CubeFace cf, 
                         Grass element, 
                         int idx) {

    auto texture_offset = element.texture_offset(cf.face);

    float minTX = this->textureAtlas.tW * texture_offset.x / this->textureAtlas.atlasW;
    float maxTX = this->textureAtlas.tW * (texture_offset.x + 1) / this->textureAtlas.atlasW;

    float minTY = this->textureAtlas.tH * texture_offset.y / this->textureAtlas.atlasH;
    float maxTY = this->textureAtlas.tH * (texture_offset.y + 1) / this->textureAtlas.atlasH;

    glm::vec3 *V = cf.vertices();

    float vertices[] = {
        V[0].x*cf.position.x, V[0].y*cf.position.y, V[0].z*cf.position.z, minTX, minTY,
        V[1].x*cf.position.x, V[1].y*cf.position.y, V[1].z*cf.position.z, maxTX, minTY,
        V[2].x*cf.position.x, V[2].y*cf.position.y, V[2].z*cf.position.z, minTX, maxTY,
        V[3].x*cf.position.x, V[3].y*cf.position.y, V[3].z*cf.position.z, maxTX, maxTY,
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_FACE_INDICES[idx]), QUAD_FACE_INDICES[idx], GL_STATIC_DRAW);

    glBindVertexArray(this->vao);

    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TEXTURE
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

const glm::vec3 DIRECTIONS[] = {
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 1),
    glm::vec3(1, 0, 0),
    glm::vec3(-1, 0, 0),
    glm::vec3(0, 0, -1),
    glm::vec3(0, -1, 0)
};

void Chunk::render_face(Grass element, CubeFace cube_face, glm::vec3 position, int idx) {
    /*
    for (const auto& d : DIRECTIONS) {
        // if (!this->blocks[position.x+d.x][position.y+d.y][position.z+d.z]) {
        if (!(position.x + d.x < 0 && position.x + d.x <= this->size &&
                position.y + d.y < 0 && position.y + d.y <= this->size &&
                position.z + d.z < 0 && position.z + d.z <= this->size
             )) {
            return;
        }
    }
    */

    auto d = DIRECTIONS[idx];

    if (position.x + d.x >= 0 && position.x + d.x < this->size && 
            position.y + d.y >= 0 && position.y + d.y < this->size && 
            position.z + d.z >= 0 && position.z + d.z < this->size && 
            this->blocks[position.x + d.x][position.y + d.y][position.z + d.z].isBlock == 1 ) {
        return;
    }

    this->shader->use();

    this->shader->setMat4("projection", state.camera.projection);
    this->shader->setMat4("view", state.camera.view);

    this->prepare_face(cube_face, element, idx);

    glBindVertexArray(this->vao);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(state.camera.model, position);
    shader->setMat4("model", model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Chunk::render_block(Grass element, glm::vec3 position) {
    this->shader->use();

    this->shader->setMat4("projection", state.camera.projection);
    this->shader->setMat4("view", state.camera.view);

    int i=0;
    for (const auto& cube_face : CUBE_FACES) {
        this->render_face(element, cube_face, position, i++);
    }
}

void Chunk::init() {
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
    glGenVertexArrays(1, &this->vao);  

    blocks.resize(this->size);
    for (int i = 0; i < this->size; i++)
        blocks[i].resize(this->size);

    for (int x = 0; x < this->size; x++) {
        for (int y = 0; y < this->size; y++) {
            for (int z = 0; z < this->size; z++) {
                this->blocks[x][y].push_back({ 1, glm::vec3(x, y, z) });
            }
        }
    }
}

void Chunk::render() {
    for (int x = 0; x < this->size; x++) {
        for (int y = 0; y < this->size; y++) {
            for (int z = 0; z < this->size; z++) {
                this->render_block(Grass(), 
                        this->blocks[x][y][z].position);
            }
        }
    }
}
