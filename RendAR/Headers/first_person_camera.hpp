#pragma once
#include "camera.hpp"

#include <vector>

#include <glad/glad.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace RendAR {
  const GLfloat YAW = -90.0f;
  const GLfloat PITCH = 0.0f;
  const GLfloat SPEED = 3.0f;
  const GLfloat SENSITIVITY = 0.025f;
  const GLfloat ZOOM = 0.25f;

  // First person
  class FirstPersonCamera : public Camera
  {
  public:
    // eular angles
    GLfloat yaw_;
    GLfloat pitch_;

    // options
    GLfloat move_speed_;
    GLfloat mouse_sensitivity_;
    GLfloat zoom_;

    bool constrain_pitch_ = true;

    // Vector Constructor
    FirstPersonCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
      :  move_speed_(SPEED), mouse_sensitivity_(SENSITIVITY), zoom_(ZOOM)
    {
      front_ = glm::vec3(0.0f, 0.0f, -1.0f);
      this->setPosition(position);
      this->world_up_ = up;
      this->yaw_ = yaw;
      this->pitch_ = pitch;
      this->updateCameraVectors();
    }

    glm::mat4 getViewMatrix() override;
    void move(CameraDirection direction, GLfloat deltaTime) override;
    void processMouse(glm::vec2& offset) override;

  private:
    void updateCameraVectors();
  };
}
