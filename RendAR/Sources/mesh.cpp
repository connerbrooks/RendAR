#include "mesh.hpp"

#include "engine.hpp"
#include "light.hpp"

namespace RendAR {
  Mesh::Mesh()
  {
    render_mode_ = GL_TRIANGLES;
  }


  Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
  {
    render_mode_ = GL_TRIANGLES;
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;
    setShader(Shader("Shaders/model.vert", "Shaders/model.frag"));
    //setColor(glm::vec3(.3f, .3f, .3f));
  }


  void
  Mesh::initBuffers()
  {
    if (vertices_.empty())
      return;

    // assumes both verteces and normals are in vertices_ vector
    // TODO: allow for separate normal buffer and vertex buffer
    //if (normals_.empty() && hasNormals_ ) {
        glGenVertexArrays(1, &VAO_);
        glGenBuffers(1, &VBO_);
        glGenBuffers(1, &EBO_);

        glBindVertexArray(VAO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);

            glBufferData(GL_ARRAY_BUFFER,
                    vertices_.size() * sizeof(Vertex),
                    &vertices_[0], GL_STATIC_DRAW);

            if (!indices_.empty()) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             indices_.size() * sizeof(GLuint),
                             &indices_[0], GL_STATIC_DRAW);
            }

            glEnableVertexAttribArray(vertex_attrib_);
            glVertexAttribPointer(vertex_attrib_, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vertex), (GLvoid*)0);

            glEnableVertexAttribArray(normal_attrib_);
            glVertexAttribPointer(normal_attrib_, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(Vertex),
                                  (GLvoid*)(offsetof(Vertex, Normal)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                  (GLvoid*)(offsetof(Vertex, TexCoords)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
        isInitialized_ = true;
        /*
    }
    else if (hasNormals_)
    {
    }
    else {
      glGenVertexArrays(1, &VAO_);
      glGenBuffers(1, &VBO_);

      glBindVertexArray(VAO_);

      glBindBuffer(GL_ARRAY_BUFFER, VBO_);
      glBufferData(GL_ARRAY_BUFFER,
                   vertices_.size() * sizeof(GLfloat),
                   &vertices_[0], GL_STATIC_DRAW);

      glVertexAttribPointer(vertex_attrib_, 3, GL_FLOAT, GL_FALSE,
                            3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(vertex_attrib_);

      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindVertexArray(0);
      isInitialized_ = true;
    }
        */

  }

  Mesh::~Mesh()
  {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
  }

  void
  Mesh::render(glm::mat4& view, glm::mat4& proj)
  {
    shader_.Use();

    if (!isInitialized_)
      initBuffers(); // init VBO, VAO

    std::vector<Light*> lights = Engine::activeScene()->getLights();

    // only 1 point light supported currently
    if (lights.size() != 0) {
        GLint lightColorLoc  = glGetUniformLocation(shader_.Program, "lightColor");
        GLint lightPosLoc    = glGetUniformLocation(shader_.Program, "lightPos");
        GLint viewPosLoc     = glGetUniformLocation(shader_.Program, "viewPos");

        glm::vec3 lightColor = lights[0]->getColor();
        glm::vec3 lightPosition = lights[0]->GetPosition();
        Camera *cam = Engine::activeScene()->getCamera();

        // lighting uniforms
        glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(lightPosLoc, lightPosition.x, lightPosition.y, lightPosition.y);
        glUniform3f(viewPosLoc, cam->Position.x, cam->Position.y, cam->Position.z);
    }

    // set color uniform
    uniform_color_ = glGetUniformLocation(shader_.Program, "objectColor");
    glUniform3f(uniform_color_, color_.x, color_.y, color_.z);

    // mvp uniforms
    uniform_model_ = glGetUniformLocation(shader_.Program, "model");
    uniform_view_ = glGetUniformLocation(shader_.Program, "view");
    uniform_projection_ = glGetUniformLocation(shader_.Program, "projection");

    glm::mat4 model = GetTransformationMatrix(); // get model transform
    glUniformMatrix4fv(uniform_view_, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(uniform_projection_, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(uniform_model_, 1, GL_FALSE, glm::value_ptr(model));

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < textures_.size(); i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      std::stringstream ss;
      std::string number;
      std::string name = textures_[i].type;
      if (name == "texture_diffuse")
        ss << diffuseNr++;
      else if (name == "texture_specular")
        ss << specularNr++;
      glUniform1f(glGetUniformLocation(shader_.Program, ("material." + name + number).c_str()), i);
      glBindTexture(GL_TEXTURE_2D, textures_[i].id);

    }
    if (textures_.empty())
        glActiveTexture(GL_TEXTURE0);

    if (wireframe_)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(VAO_);

    if (indices_.empty())
        glDrawArrays(render_mode_, 0, vertices_.size());
    else
        glDrawElements(render_mode_, indices_.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    if (wireframe_)
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
