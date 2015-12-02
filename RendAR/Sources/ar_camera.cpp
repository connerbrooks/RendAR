#include "ar_camera.hpp"

namespace RendAR {
  ARCamera::ARCamera()
  {
    SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  }

  ARCamera::ARCamera(glm::vec3& pos)
  {
    SetPosition(pos);
  }

  glm::mat4 ARCamera::GetViewMatrix()
  {
    return GetTransformationMatrix();
  }
}