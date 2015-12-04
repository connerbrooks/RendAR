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

  void
  ARCamera::setInfiniTAMPose(glm::mat4 transform)
  {
    SetTransformationMatrix(transform);

    // fix rotation x axis
    glm::quat rot = GetRotation();
    rot.x = -rot.x;

    // fix y and z translation axes
    glm::vec3 pos = GetPosition();
    pos.y *= -1.0f;
    pos.z *= -1.0f;

    SetPosition(pos);
    SetRotation(rot);
  }
}