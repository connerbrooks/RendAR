#pragma once
#include <vector>
#include "transform.hpp"
#include "shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RendAR
{
  class Object : public Transform {
  public:
    Object();
    ~Object();

    void setVertices(const std::vector<GLfloat>& vertices);
    void setVertices(const std::vector<GLfloat>& vertices,
                     const std::vector<GLushort>& indices);
    void setVertices(const std::vector<GLfloat>& vertices,
                     const std::vector<GLfloat>& normals);
    void setShader(const Shader& shader);
    void setColor(const glm::vec3& color);
    glm::vec3 getColor();
    virtual void render(glm::mat4& view, glm::mat4& proj) = 0;

    void setWireframe(bool w);

  protected:
    std::vector<GLushort> indices_;
    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> normals_;

    Shader shader_;
    GLuint VBO_, VAO_;

    bool isInitialized_ = false;
    bool hasNormals_ = false;

    glm::vec3 color_;

    GLenum render_mode_;
    GLint uniform_model_;
    GLint uniform_view_;
    GLint uniform_projection_;
    GLint uniform_color_;

    GLint vertex_attrib_ = 0;
    GLint normal_attrib_ = 1;

    bool wireframe_ = false;
  };
}
