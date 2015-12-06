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

  void setPosition(const glm::vec3& position);
  glm::vec3 getPosition() const;

  void setRotation(const glm::quat& rotation);
  glm::quat getRotation() const;

  void setScale(const glm::vec3& scale);
  glm::vec3 getScale() const;

  void translate(const glm::vec3& translation);

  void setTransformationMatrix(const glm::mat4& transform_mat);
  glm::mat4 getTransformationMatrix() const;

  void setParent(Transform* transform);

  const Transform* getParent() const ;
  Transform* getParent() ;

 private:
  Transform* parent_;

  glm::vec3 position_;
  glm::quat rotation_;
  glm::vec3 scale_;
};
}
