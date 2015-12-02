#include "context.hpp"

namespace RendAR {
  Context::Context()
  {}

  ContextConfig
  Context::getContextConfig() { return config_; }

  void
  Context::setClearColor(const glm::vec3& color)
  {
    clear_color_ = color;
  }
}
