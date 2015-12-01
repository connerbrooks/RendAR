#include "light.hpp"

namespace RendAR {
  Light::Light()
  {
    setShader(Shader("Shaders/default.vert", "Shaders/default.frag"));
    SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
    setColor(glm::vec3(1.0f, 1.0f, 1.0f));
  }
}
