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

// scene objects
Camera* camera;
Cube* cube;
Cube* cube1;
Light* light;

// controls
GLfloat lastX = 400, lastY = 400;
bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool firstMouse = true;

void
do_movement();

// control callbacks
void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void
mouse_callback(GLFWwindow *window, double xpos, double ypos);

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

  light->SetPosition(vec3(1.0f + sin(glfwGetTime()) * 2.0f,
                          sin(glfwGetTime() / 2.0f) * 1.0f,
                          0.0f));

  // rotate around axis
  vec3 EulerAngles(-(GLfloat)glfwGetTime(), 45, 0);
  cube->SetRotation(quat(EulerAngles));
  cube1->SetRotation(quat(EulerAngles));
}

int main(int argc, char * argv[]) {

  Engine::init(argc, argv);

  // todo: not this
  auto glfw_context = dynamic_cast<GLFW3Context*>(Engine::context()); 
  glfw_context->setKeyCallBack(&key_callback);
  glfw_context->setCursorPosCallback(&mouse_callback);

  glfw_context->setClearColor(vec3(0.0f, 0.0f, 0.0f));

  Scene* scene = Engine::activeScene();
  camera = new Camera(vec3(0.0f, 0.0f, 3.0f));

  scene->setCamera(camera);

  light = new Light();
  light->SetPosition(vec3(0.0f, 3.0f, 0.0f));

  cube = new Cube();
  cube->SetPosition(vec3(0.0f, 0.0f, 2.0f));

  Cube *floor = new Cube();
  floor->SetScale(vec3(20.0f, .2f, 20.0f));
  floor->SetPosition(vec3(0, -4, 0));

  cube1 = new Cube();
  cube1->setShader(Shader("Shaders/default.vert", "Shaders/default.frag"));
  cube1->SetPosition(vec3(-1.0f, -0.4f, -3.0f));
  cube1->setColor(vec3(0.9f, 0.1f, .45f));
  cube1->setWireframe(true);
  cube1->SetParent(cube);

  // add objects to scene
  scene->add(floor);
  scene->add(cube);
  scene->add(cube1);
  scene->add(light);

  Engine::startMainLoop(&updateLoop);
}


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
