#include "object.hpp"

namespace RendAR {
  Object::Object() {}
  Object::~Object() {}

  void Object::setVertices(const std::vector<Vertex>& vertices)
  {
    vertices_ = vertices;
  }

  void Object::setVertices(const std::vector<Vertex>& vertices,
                           const std::vector<GLuint>& indices)
  {
    vertices_ = vertices;
    indices_ = indices;
  }

  void Object::setShader(const Shader& shader)
  {
    shader_ = shader;
  }

  void Object::setColor(const glm::vec3& color)
  {
    color_ = color;
  }

  glm::vec3
  Object::getColor()
  {
    return color_;
  }

  void
  Object::setWireframe(bool w)
  {
    wireframe_ = w;
  }
}
