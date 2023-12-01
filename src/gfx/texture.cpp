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
