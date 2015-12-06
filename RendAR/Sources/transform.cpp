#include "transform.hpp"

#include "glm/gtx/matrix_decompose.hpp"

namespace RendAR {

Transform::Transform()
  : parent_(nullptr),
    position_(0.0f, 0.0f, 0.0f),
    rotation_(1.0f, 0.0f, 0.0f, 0.0f),
    scale_(1.0f, 1.0f, 1.0f) {
}

Transform::~Transform() {
  // Objects are not responsible for deleting their parents.
}

void Transform::setPosition(const glm::vec3& position) {
  position_ = position;
}

glm::vec3 Transform::getPosition() const {
  return position_;
}

void Transform::setRotation(const glm::quat& rotation) {
  rotation_ = rotation;
}

glm::quat Transform::getRotation() const {
  return rotation_;
}

void Transform::setScale(const glm::vec3& scale) {
  scale_ = scale;
}

glm::vec3 Transform::getScale() const {
  return scale_;
}

void Transform::translate(const glm::vec3& translation) {
  position_ += translation;
}

void Transform::setTransformationMatrix(const glm::mat4& transform_mat) {
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(transform_mat, scale_, rotation_, position_, skew, perspective);
}

glm::mat4 Transform::getTransformationMatrix() const {
  glm::mat4 trans_mat = glm::scale(glm::mat4_cast(rotation_), scale_);
  trans_mat[3][0] = position_.x;
  trans_mat[3][1] = position_.y;
  trans_mat[3][2] = position_.z;
  glm::mat4 parent_mat = glm::mat4(1.0f);
  if (parent_ != NULL) {
    parent_mat = parent_->getTransformationMatrix();
    trans_mat = parent_mat * trans_mat;
  }
  return  trans_mat;
}

void Transform::setParent(Transform* transform) {
  parent_ = transform;
}

const Transform* Transform::getParent() const {
  return parent_;
}

Transform* Transform::getParent() {
  return parent_;
}

}
