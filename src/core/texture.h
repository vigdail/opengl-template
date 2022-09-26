#pragma once

#include "gl/texture.hpp"
#include "stb_image.h"

#include <memory>
#include <filesystem>

std::shared_ptr<gl::texture_2d> load_texture(const std::filesystem::path& path);
