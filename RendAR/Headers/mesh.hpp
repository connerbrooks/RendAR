#pragma once
#include "object.hpp"

namespace RendAR
{
  class Mesh : public Object {
  public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    ~Mesh();
    void initBuffers();
    virtual void render(glm::mat4& view, glm::mat4& proj) override;
  };
}
