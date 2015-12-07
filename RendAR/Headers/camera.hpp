#pragma once
#include "transform.hpp"

#include <glad/glad.h>

namespace RendAR {
  enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
  };

  class Camera : public Transform {
  public:
    Camera() {};
    ~Camera() {};
    virtual glm::mat4 getViewMatrix() = 0;
    virtual void move(CameraDirection dir, GLfloat deltaTime) {};
    virtual void processMouse(glm::vec2& offset) {};

  protected:
    double aspect_;
    double fov_;
    double near_;
    double far_;

    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;
    glm::mat4 view_;
  };
}