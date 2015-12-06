#pragma once
#define CAMERA_H
#include "camera.hpp"

#include <vector>
#include <glad/glad.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RendAR {
  enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
  };

  const GLfloat YAW = -90.0f;
  const GLfloat PITCH = 0.0f;
  const GLfloat SPEED = 3.0f;
  const GLfloat SENSITIVITY = 0.025f;
  const GLfloat ZOOM = 0.25f;

  class QuatCamera : public Camera
  {
  public:
    virtual glm::mat4 getViewMatrix() override;
    virtual void move(CameraDirection dir) override;
  private:
  };
}
