// Local Headers
#include "rendar.hpp"
#include "engine.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "light.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>

using namespace RendAR;
using namespace glm;

Camera* camera;
Cube* cube;
Light* light;

GLfloat lastX = 400, lastY = 400;
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void do_movement()
{
  if (keys[GLFW_KEY_W])
    camera->ProcessKeyboard(FORWARD, deltaTime);
  if (keys[GLFW_KEY_S])
    camera->ProcessKeyboard(BACKWARD, deltaTime);
  if (keys[GLFW_KEY_A])
    camera->ProcessKeyboard(LEFT, deltaTime);
  if (keys[GLFW_KEY_D])
    camera->ProcessKeyboard(RIGHT, deltaTime);
}

/*
 * Main game loop.
 * Updates to objects go here.
 */
void updateLoop()
{
  // camera updates
  GLfloat currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  do_movement();

  // move cube away
  //cube->SetPosition(vec3(-(GLfloat)glfwGetTime() / 5.0, 0.0f, 0.0f));

  light->SetPosition(vec3(1.0f + sin(glfwGetTime()) * 2.0f, sin(glfwGetTime() / 2.0f) * 1.0f, 0.0f));

  // rotate around axis
  vec3 EulerAngles(-(GLfloat)glfwGetTime(), 45, 0);
  cube->SetRotation(quat(EulerAngles));
}

void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  //GLfloat cameraSpeed = 0.05f;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
  }
}

bool firstMouse = true;

void
mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera->ProcessMouseMovement(xoffset, yoffset);
}


int main(int argc, char * argv[]) {

  Engine::init(argc, argv);

  auto glfw_context = dynamic_cast<GLFW3Context*>(Engine::context()); // todo: not this
  glfw_context->setKeyCallBack(&key_callback);
  glfw_context->setCursorPosCallback(&mouse_callback);

  Scene* scene = Engine::activeScene();
  camera = new Camera(vec3(0.0f, 0.0f, 3.0f));

  scene->setCamera(camera);

  light = new Light();
  light->SetPosition(vec3(0.0f, 3.0f, 0.0f));

  cube = new Cube();
  cube->SetPosition(vec3(0.0f, 0.0f, 1.0f));


  scene->add(cube);
  scene->add(light);

  Cube* cube1 = new Cube();
  cube1->setShader(Shader("Shaders/default.vert", "Shaders/default.frag"));
  cube1->SetPosition(vec3(-1.0f, -0.4f, -3.0f));
  scene->add(cube1);

  Engine::startMainLoop(&updateLoop);
}
