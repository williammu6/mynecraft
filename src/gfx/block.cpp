#include "block.hpp"
#include "gfx.hpp"

Block::Block(unsigned int _texture) {
    float tileW = 200;
    float tileH = 200;
    float tilesX = 3;
    float tilesY = 1;
    float atlasW = tileW * tilesX;
    float atlasH = tileH * tilesY;
    int sideOffsetX = 2, sideOffsetY = 1;
    int topOffsetX = 1, topOffsetY = 1;
    int bottomOffsetX = 0, bottomOffsetY = 1;
    

    texture = _texture;

    float vertices[] = {
        // positions          // texture coords
        // FRONT
        -0.5f, -0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
        0.5f, -0.5f,   0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY)/atlasH,  // BOTTOM RIGHT
        0.5f,  0.5f,   0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT

        0.5f,  0.5f,   0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT
        -0.5f,  0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP LEFT
        -0.5f, -0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
                                                                                      //
        // TOP
        -0.5f, 0.5f,  -0.5f,  tileW*(topOffsetX)/atlasW, tileH*(topOffsetY)/atlasH, // BOTTOM LEFT
        0.5f,  0.5f,  -0.5f,  tileW*(topOffsetX+1)/atlasW, tileH*(topOffsetY)/atlasH,  // BOTTOM RIGHT
        0.5f,  0.5f,  0.5f,  tileW*(topOffsetX+1)/atlasW, tileH*(topOffsetY+1)/atlasH, // TOP RIGHT

        0.5f,  0.5f,  0.5f,  tileW*(topOffsetX+1)/atlasW, tileH*(topOffsetY+1)/atlasH, // TOP RIGHT
        -0.5f, 0.5f,  0.5f,  tileW*(topOffsetX)/atlasW, tileH*(topOffsetY+1)/atlasH, // TOP LEFT
        -0.5f, 0.5f,  -0.5f,  tileW*(topOffsetX)/atlasW, tileH*(topOffsetY)/atlasH, // BOTTOM LEFT
        
        // RIGHT
        0.5f, -0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
        0.5f,  0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY+1)/atlasH,  // BOTTOM RIGHT
        0.5f,  0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT

        0.5f,  0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT
        0.5f, -0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY)/atlasH, // TOP LEFT
        0.5f, -0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
        
        // LEFT
        -0.5f, -0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
        -0.5f,  0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY+1)/atlasH,  // BOTTOM RIGHT
        -0.5f,  0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT

        -0.5f,  0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY+1)/atlasH, // TOP RIGHT
        -0.5f, -0.5f,  0.5f,  tileW*(sideOffsetX)/atlasW, tileH*(sideOffsetY)/atlasH, // TOP LEFT
        -0.5f, -0.5f,  -0.5f,  tileW*(sideOffsetX+1)/atlasW, tileH*(sideOffsetY)/atlasH, // BOTTOM LEFT
    };


    float indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);  
    glBindVertexArray(vao);

    glGenBuffers(1, &ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Block::prepareDraw() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
