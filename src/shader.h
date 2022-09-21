#pragma once

#include <gl/program.hpp>

#include <memory>

std::shared_ptr<gl::program> load_shader(const char* vert_path, const char* frag_path);
