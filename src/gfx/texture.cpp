#include "texture.hpp"
#include "glad/glad.h"

void load_pixels(const char *path, unsigned char **pixels_out, int *width_out,
                 int *height_out) {
  int width, height, channels;

  unsigned char *image = stbi_load(path, &width, &height, &channels, 0);

  size_t size = width * height * 4;

  *pixels_out = (unsigned char *)malloc(size);
  memcpy(*pixels_out, image, size);
  *width_out = width;
  *height_out = height;

  stbi_image_free(image);
}

Texture from_pixels(unsigned char *pixels, int width, int height) {
  struct Texture tex = {.width = width, .height = height};
  glGenTextures(1, &tex.pixels);
  glBindTexture(GL_TEXTURE_2D, tex.pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  return tex;
}

Texture texture_from_path(const char *path) {
  unsigned char *pixels;

  int width, height, nrChannels;

  load_pixels(path, &pixels, &width, &height);
  Texture tex = from_pixels(pixels, width, height);
  free(pixels);

  return tex;
}
