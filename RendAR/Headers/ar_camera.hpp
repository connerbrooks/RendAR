#pragma once
#define CAMERA_H
#include "camera.hpp"

namespace RendAR {
  class ARCamera : public Camera
  {
  public:
    ARCamera();
    ARCamera(glm::vec3& pos);
    glm::mat4 GetViewMatrix() override;
  };
}
