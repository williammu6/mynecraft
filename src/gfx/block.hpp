#pragma once

class Block {
    protected: 
        unsigned int vao, vbo, ebo, texture;
    public:
        Block(unsigned int _texture);
        void prepareDraw();
};

