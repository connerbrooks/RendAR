#include "pyramid.hpp"

namespace RendAR {




  Pyramid::Pyramid()
  {
    GLfloat vertices[] = {
      -1.0f, -1.0f, -1.0f, // 0. left-back
      1.0f, -1.0f, -1.0f, // 1. right-back
      1.0f, -1.0f, 1.0f, // 2. right-front
      -1.0f, -1.0f, 1.0f, // 3. left-front
      0.0f, 0.0f, 0.0f, // 4. top
      0.0f, -1.0f, 0.0f // 5. bottom
    };

    GLuint indices[] = { // Vertex indices of the 8 Triangles
      //top pyramid
      2, 4, 3, // front face (CCW) - same as 4,3,2 or 3,2,4
      4, 2, 1, // right face  - same as 2,1,4 or 1,4,2
      0, 4, 1, // back face - same 4,1,0 or 1,0,4
      4, 0, 3, // left face - same 0,3,4 or 3,4,2
    };

    for (GLuint i = 0; i < sizeof(vertices) / sizeof(GLfloat); i += 3) {
      Vertex vert;
      glm::vec3 v;
      v.x = vertices[i];
      v.y = vertices[i + 1];
      v.z = vertices[i + 2];
      vert.Position = v;

      //v.x = vertices[i + 3];
      //v.y = vertices[i + 4];
      //v.z = vertices[i + 5];
      //vert.Normal = v;

      glm::vec2 t(0.0f, 0.0f);
      vert.TexCoords = t;
      vertices_.push_back(vert);
    }

    for (GLuint i = 0; i < sizeof(indices) / sizeof(GLuint); ++i)  {
      indices_.push_back(indices[i]);
    }

    setShader(Shader("Shaders/default.vert", "Shaders/default.frag"));
    setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  }
}