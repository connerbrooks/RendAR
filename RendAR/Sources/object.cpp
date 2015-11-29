#include "object.hpp"

namespace RendAR {
  Object::Object() {
    //shader_ = Shader("shaders/default.vs", "shaders/default.fs");
  }
  Object::~Object() {}

  void Object::setVertices(const std::vector<GLfloat>& vertices) {
    vertices_ = vertices;
  }

  void Object::setVertices(const std::vector<GLfloat>& vertices,
                                   const std::vector<GLushort>& indices) {
    vertices_ = vertices;
    indices_ = indices;
  }

  void Object::setVertices(const std::vector<GLfloat>& vertices,
                                   const std::vector<GLfloat>& normals) {
    vertices_ = vertices;
    normals_ = normals;
  }

  void Object::setShader(const Shader& shader)
  {
    shader_ = shader;
  }

  void Object::setColor(const glm::vec3& color)
  {
    color_ = color;
  }
}
