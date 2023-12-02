#include "texture.hpp"
#include "glad/glad.h"

typedef struct {
  unsigned char *pixels;
  int width;
  int height;
} Image;

Image loadPixels(const char *path) {
  Image image;

  int width, height, channels;

  image.pixels = stbi_load(path, &width, &height, &channels, 0);

  if (!image.pixels) {
    fprintf(stderr, "Error loading image at %s\n", path);
    return image;
  }

  image.width = width;
  image.height = height;

  return image;
}

Texture textureFromPixels(const Image *image) {
  struct Texture texture = {.width = image->width, .height = image->height};

  glGenTextures(1, &texture.pixels);
  glBindTexture(GL_TEXTURE_2D, texture.pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->width, image->height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  return texture;
}

Texture textureFromPath(const char *path) {
  Image image = loadPixels(path);
  Texture texture = textureFromPixels(&image);
  free(image.pixels);
  return texture;
}

Texture cubemapTextureFromPath(const std::array<char *, 6> textureFaces) {
  Texture texture;
  glGenTextures(1, &texture.pixels);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture.pixels);

  int width, height, nrChannels;
  unsigned char *data;
  for (unsigned int i = 0; i < textureFaces.size(); i++) {
    data = stbi_load(textureFaces[i], &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  texture.width = width;
  texture.height = height;

  return texture;
}
