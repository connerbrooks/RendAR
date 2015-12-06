#pragma once
#include <vector>
#include "transform.hpp"
#include "shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>

namespace RendAR
{
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Texture {
    GLuint id;
    std::string type;
    aiString path;
  };

  class Object : public Transform {
  public:
    Object();
    ~Object();

    void setVertices(const std::vector<Vertex>& vertices);
    void setVertices(const std::vector<Vertex>& vertices,
                     const std::vector<GLuint>& indices);
    void setShader(const Shader& shader);
    void setColor(const glm::vec3& color);
    glm::vec3 getColor();
    virtual void render(glm::mat4& view, glm::mat4& proj) = 0;

    void setWireframe(bool w);

  protected:
    std::vector<GLuint> indices_;
    std::vector<Vertex> vertices_;

    std::vector<Texture> textures_loaded_;
    std::vector<Texture> textures_;

    Shader shader_;
    glm::vec3 color_ = glm::vec3(1.0f);

    GLuint VBO_, VAO_, EBO_;
    GLenum render_mode_;
    GLenum buffer_mode_;
    GLint uniform_model_;
    GLint uniform_view_;
    GLint uniform_projection_;
    GLint uniform_color_;

    GLint vertex_attrib_ = 0;
    GLint normal_attrib_ = 1;

    bool wireframe_ = false;
    bool isInitialized_ = false;
  };
}
