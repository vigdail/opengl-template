#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::shared_ptr<gl::texture_2d> load_texture(const std::filesystem::path& path) {
  if (!exists(path)) {
    throw std::runtime_error("File not found: " + path.string());
  }
  int width = 0;
  int height = 0;
  int channels = 0;
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

  std::shared_ptr<gl::texture_2d> texture(new gl::texture_2d());
  texture->set_storage(1, GL_RGBA8, width, height);
  texture->set_sub_image(0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
  texture->set_wrap_s(GL_REPEAT);
  texture->set_wrap_t(GL_REPEAT);
  texture->set_min_filter(GL_NEAREST);
  texture->set_mag_filter(GL_LINEAR);

  stbi_image_free(data);

  return texture;
}
