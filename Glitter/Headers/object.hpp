#pragma once

#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace RendAR
{
  class Object {
  public:
    Object();
    ~Object();
    //void render(glm::mat4& view, glm::mat4& proj);
    void render();

    Shader* shader_;
    GLuint VBO, VAO;
    //virtual void render() = 0;

  };
}
