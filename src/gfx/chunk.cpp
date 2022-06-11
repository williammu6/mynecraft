#include "chunk.hpp"
#include "../state.hpp"

void Chunk::prepare_face(CubeFace cf, 
                         Grass element) {

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(QUAD_FACE_INDICES[cf.ID]), QUAD_FACE_INDICES[cf.ID], GL_STATIC_DRAW);

    glBindVertexArray(this->vao);
    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TEXTURE
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


int Chunk::render_face(Grass element, CubeFace cube_face, Block& block) {
    auto face_direction = DIRECTIONS[cube_face.ID];

    int nx = block.normalPosition.x + face_direction.x;
    int ny = block.normalPosition.y + face_direction.y;
    int nz = block.normalPosition.z + face_direction.z;

    if (nx >= 0 && ny >= 0 && nz >= 0 && nx < this->dimentions.x && ny < this->dimentions.y && nz < this->dimentions.z &&
            this->blocks[nx][ny][nz].isBlock == 1) {
        return 0;
    }

    this->prepare_face(cube_face, element);

    glBindVertexArray(this->vao);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(state.camera.model, block.position);
    shader->setMat4("model", model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 1;
}

int Chunk::render_block(Grass element, Block& block) {
    int rendered = 0;
    for (int i = 0; i < 6; i++) {
        auto cube_face = CUBE_FACES[i];
        rendered |= this->render_face(element, cube_face, block);
    }
    return rendered;
}

void Chunk::render() {
    this->shader->setMat4("view", state.camera.view);
    for (int x = 0; x < this->dimentions.x; x++) {
        for (int z = 0; z < this->dimentions.z; z++) {
            for (int y = 0; y < this->dimentions.y; y++) {
                auto& block = this->blocks[x][y][z];
                if (((state.camera.cameraFront.x < 0 && block.position.x - 10 < state.camera.cameraPos.x) ||
                        (state.camera.cameraFront.x > 0 && block.position.x + 10 > state.camera.cameraPos.x)) &&
                        ((state.camera.cameraFront.z < 0 && block.position.z - 10 < state.camera.cameraPos.z) ||
                        (state.camera.cameraFront.z > 0 && block.position.z + 10 > state.camera.cameraPos.z))) {
                    int rendered = this->render_block(Grass(), block);
                    if (!rendered) break;
                }
            }
        }
    }
}

void Chunk::init() {
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
    glGenVertexArrays(1, &this->vao);  

    this->blocks.resize(this->dimentions.x);
    for (int i = 0; i < this->dimentions.x; i++)
        this->blocks[i].resize(this->dimentions.x);

    for (int x = 0; x < this->dimentions.x; x++) {
        for (int y = 0; y < this->dimentions.y; y++) {
            for (int z = 0; z < this->dimentions.z; z++) {
                printf("%d %d %d\n", x, y, z);
                this->blocks[x][y].push_back({ 1, glm::vec3(x, y, z), glm::vec3(x, this->seaLevel - y , z) + this->position  });
            }
        }
    }
    this->shader->use();
    this->shader->setMat4("projection", state.camera.projection);
}
