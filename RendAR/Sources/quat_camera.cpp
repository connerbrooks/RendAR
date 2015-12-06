#include "quat_camera.hpp"

namespace RendAR {

  void update()
  {
    
  }

  glm::mat4 QuatCamera::getViewMatrix()
  {
  }

  void QuatCamera::move(CameraDirection dir)
  {
    switch (dir) {
    case UP:
      break;
    case DOWN:
      break;
    case LEFT:
      break;
    case RIGHT:
      break
    case FORWARD:
      break;
    case BACK:
      break
    }
  }
}