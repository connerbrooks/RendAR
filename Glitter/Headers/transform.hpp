#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RendAR {
class Transform {
 public:
  Transform();
  virtual ~Transform();

  Transform(const Transform& other) = delete;
  const Transform& operator=(const Transform& rhs) = delete;

  void SetPosition(const glm::vec3& position);
  glm::vec3 GetPosition() const;

  void SetRotation(const glm::quat& rotation);
  glm::quat GetRotation() const;

  void SetScale(const glm::vec3& scale);
  glm::vec3 GetScale() const;

  void Translate(const glm::vec3& translation);

  void SetTransformationMatrix(const glm::mat4& transform_mat);
  glm::mat4 GetTransformationMatrix() const;

  void SetParent(Transform* transform);

  const Transform* GetParent() const ;
  Transform* GetParent() ;

 private:
  Transform* parent_;

  glm::vec3 position_;
  glm::quat rotation_;
  glm::vec3 scale_;
};
}
