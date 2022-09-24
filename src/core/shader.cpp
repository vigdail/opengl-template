#include "shader.h"

std::shared_ptr<gl::program> load_shader(const char* vert_path, const char* frag_path) {
  gl::shader vert(GL_VERTEX_SHADER);
  vert.load_source(vert_path);
  if (!vert.compile()) {
    std::cerr << vert.info_log() << '\n';
  }

  gl::shader frag(GL_FRAGMENT_SHADER);
  frag.load_source(frag_path);
  if (!frag.compile()) {
    std::cerr << frag.info_log() << '\n';
  }

  std::shared_ptr<gl::program> program(new gl::program);
  program->attach_shader(vert);
  program->attach_shader(frag);
  if (!program->link()) {
    std::cerr << program->info_log() << '\n';
  }

  return program;
}
