#pragma once
#define CAMERA_H

#include <vector>

#include <glad/glad.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.025f;
const GLfloat ZOOM = 0.25f;


class Camera
{
public:
  // camera attr
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  // eular angles
  GLfloat Yaw;
  GLfloat Pitch;

  // options
  GLfloat MovementSpeed;
  GLfloat MouseSensitivity;
  GLfloat Zoom;

  // Vector Constructor
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
  {
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
  }

  // Scalar Constructor
  Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
  {
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
  }

  // Return view matrix 
  glm::mat4 GetViewMatrix()
  {
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
  }

  void
  ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
  {
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
      this->Position += this->Front * velocity;
    if (direction == BACKWARD)
      this->Position -= this->Front * velocity;
    if (direction == LEFT)
      this->Position -= this->Right * velocity;
    if (direction == RIGHT)
      this->Position += this->Right * velocity;
  }

  void
  ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
  {
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw += xoffset;
    this->Pitch += yoffset;

    if (constrainPitch) {
      if (this->Pitch > 89.0f)
        this->Pitch = 89.0f;
      if (this->Pitch < -89.0f)
        this->Pitch = -89.0f;
    }

    this->updateCameraVectors();
  }

private:
  void
  updateCameraVectors()
  {
    glm::vec3 front;
    front.x = cos(this->Yaw) * cos(this->Pitch);
    front.y = sin(this->Pitch);
    front.z = sin(this->Yaw) * cos(this->Pitch);
    this->Front = glm::normalize(front);
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
  }

};
