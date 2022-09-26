#include "example_layer.h"

#include "core/application.h"

int main() {
  Application app("OpenGL", 1280, 720);
  app.push_layer(std::make_unique<ExampleLayer>(1280.0f / 720.0f));
  app.run();
  return 0;
}
