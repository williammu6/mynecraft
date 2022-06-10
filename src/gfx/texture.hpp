#pragma once

#include "vendor/stb_image.h"
#include "gfx.hpp"
#include <iostream>

unsigned int createTextureFromPath(std::string& path);

struct TextureAtlas {
    unsigned int texture;

    int tW = 128;
    int tH = 128;

    int atlasW = 256;
    int atlasH = 256;

    TextureAtlas() = default;
    TextureAtlas(std::string& path) {
        this->texture = createTextureFromPath(path);
    }
};
