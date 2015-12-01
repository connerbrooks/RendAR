#pragma once

#include "glm/common.hpp"

namespace RendAR {
  class Material {
  public:
    Material();
    ~Material() {};

  private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

  };
}
