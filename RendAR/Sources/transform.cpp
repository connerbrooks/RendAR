#include "transform.hpp"

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

void Transform::SetPosition(const glm::vec3& position) {
  position_ = position;
}

glm::vec3 Transform::GetPosition() const {
  return position_;
}

void Transform::SetRotation(const glm::quat& rotation) {
  rotation_ = rotation;
}

glm::quat Transform::GetRotation() const {
  return rotation_;
}

void Transform::SetScale(const glm::vec3& scale) {
  scale_ = scale;
}

glm::vec3 Transform::GetScale() const {
  return scale_;
}

void Transform::Translate(const glm::vec3& translation) {
  position_ += translation;
}

/*
void Transform::SetTransformationMatrix(const glm::mat4& transform_mat) {
  util::DecomposeMatrix(transform_mat, position_, rotation_, scale_);
}
*/

glm::mat4 Transform::GetTransformationMatrix() const {
  glm::mat4 trans_mat = glm::scale(glm::mat4_cast(rotation_), scale_);
  trans_mat[3][0] = position_.x;
  trans_mat[3][1] = position_.y;
  trans_mat[3][2] = position_.z;
  glm::mat4 parent_mat = glm::mat4(1.0f);
  if (parent_ != NULL) {
    parent_mat = parent_->GetTransformationMatrix();
    trans_mat = parent_mat * trans_mat;
  }
  return  trans_mat;
}

void Transform::SetParent(Transform* transform) {
  parent_ = transform;
}

const Transform* Transform::GetParent() const {
  return parent_;
}

Transform* Transform::GetParent() {
  return parent_;
}

}
