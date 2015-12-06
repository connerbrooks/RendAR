#include "euler_camera.hpp"

namespace RendAR {
    glm::mat4 EulerCamera::getViewMatrix()
    {
      return glm::lookAt(this->getPosition(), this->getPosition() + this->front_, this->up_);
    }

  void
    EulerCamera::move(CameraDirection direction, GLfloat deltaTime)
    {
      GLfloat velocity = this->move_speed_ * deltaTime;
      switch (direction) {
      case FORWARD:
        this->setPosition(getPosition() + this->front_ * velocity);
        break;
      case BACK:
        this->setPosition(getPosition() - this->front_ * velocity);
        break;
      case LEFT:
        this->setPosition(getPosition() - this->right_ * velocity);
        break;
      case RIGHT:
        this->setPosition(getPosition() + this->right_ * velocity);
        break;
      }
    }

    void
    EulerCamera::processMouse(glm::vec2& offset)
    {
      offset *= mouse_sensitivity_;

      this->yaw_ += offset.x;
      this->pitch_ += offset.y;

      if (constrain_pitch_) {
        if (pitch_ > glm::radians(89.0f))
          pitch_ = glm::radians(89.0f);
        if (pitch_ < glm::radians(-89.0f))
          pitch_ = glm::radians(-89.0f);
      }

      updateCameraVectors();
    }

    void EulerCamera::updateCameraVectors()
    {
      glm::vec3 front;
      front.x = cos(this->yaw_) * cos(this->pitch_);
      front.y = sin(this->pitch_);
      front.z = sin(this->yaw_) * cos(this->pitch_);
      this->front_ = glm::normalize(front);
      this->right_ = glm::normalize(glm::cross(this->front_, this->world_up_));
      this->up_ = glm::normalize(glm::cross(this->right_, this->front_));
    }



}