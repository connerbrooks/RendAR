#pragma once
#include "object.hpp"

namespace RendAR
{
  class Cube : public Object {
  public:
    Cube();
    ~Cube();

    virtual void render(glm::mat4& view, glm::mat4& proj) override;
  };
}
