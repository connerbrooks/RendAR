#pragma once
#define CAMERA_H

#include <vector>

#include <glad/glad.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "transform.hpp"

namespace RendAR {
  /*
  enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
  };
  */

  //const GLfloat YAW = -90.0f;
  //const GLfloat PITCH = 0.0f;
  //const GLfloat SPEED = 3.0f;
  //const GLfloat SENSITIVITY = 0.025f;
  //const GLfloat ZOOM = 0.25f;

  class ARCamera : public Transform
  {
  public:
    // camera attr
    //glm::vec3 Position;
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
    ARCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
      SetPosition(position);
      this->WorldUp = up;
      this->Yaw = yaw;
      this->Pitch = pitch;
      this->updateCameraVectors();
    }

    // Scalar Constructor
    ARCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
      SetPosition(glm::vec3(posX, posY, posZ));
      this->WorldUp = glm::vec3(upX, upY, upZ);
      this->Yaw = yaw;
      this->Pitch = pitch;
      this->updateCameraVectors();
    }

    // Return view matrix 
    glm::mat4 GetViewMatrix()
    {
      /*
      Yaw = glm::yaw(GetRotation());
      Pitch = glm::pitch(GetRotation());
      updateCameraVectors();
      return glm::lookAt(GetPosition(), GetPosition() + this->Front, this->Up);
      */
      glm::quat rot = GetRotation();

      return GetTransformationMatrix();
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
}
