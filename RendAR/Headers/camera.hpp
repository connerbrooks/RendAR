#pragma once
#define CAMERA_H
#include "transform.hpp"

namespace RendAR {

  class Camera : public Transform
  {
  public:

    Camera() {};
    ~Camera() {};
    virtual glm::mat4 GetViewMatrix() = 0;
  };
}
