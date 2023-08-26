#include "texture.hpp"

void load_pixels(const char *path, unsigned char **pixels_out, int *width_out,
                 int *height_out) {
  int width, height, channels;

  unsigned char *image = stbi_load(path, &width, &height, &channels, 0);

  size_t size = width * height * 4;

  *pixels_out = (unsigned char*)malloc(size);
  memcpy(*pixels_out, image, size);
  *width_out = width;
  *height_out = height;

  stbi_image_free(image);
}

Texture texture_from_path(const char *path) {
  unsigned char *pixels;

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;

  load_pixels(path, &pixels, &width, &height);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  Texture tex = {
    .texture = pixels,
    .width = width,
    .height = height
  };
  
  free(pixels);

  return tex;
}
