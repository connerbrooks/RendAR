#pragma once
#include "transform.hpp"

namespace RendAR {
  enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
  };

  class Camera : public Transform {
  public:
    Camera() {};
    ~Camera() {};
    virtual glm::mat4 getViewMatrix() = 0;
    virtual void move(CameraDirection dir) = 0;

  private:
    double aspect_;
    double fov_;
    double near_;
    double far_;

    glm::vec3 camera_up_;
    glm::mat4 view_;
  };
}