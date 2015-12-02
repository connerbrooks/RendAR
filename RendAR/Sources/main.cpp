// Local Headers
#include "rendar.hpp"
#include "engine.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "light.hpp"
<<<<<<< HEAD
#include "model.hpp"
=======
#include "ar_camera.hpp"

#include "../../../ITMLib/Engine/ITMMainEngine.h"
#include "../../../ITMLib/Utils/ITMLibSettings.h"
#include "../../../Engine/ImageSourceEngine.h"
#include "../../../Engine/OpenNIEngine.h"

#include "../../../Utils/NVTimer.h"
#include "../../../Utils/FileUtils.h"
>>>>>>> 5df4ef7... Add necessary dependencies for using as an InfiniTAM sub project. OpenGL camera pose set by infinitam.

// Standard Headers
#include <cstdio>
#include <cstdlib>

using namespace std;
using namespace glm;
using namespace RendAR;
using namespace InfiniTAM::Engine;

// scene objects
ARCamera* camera;
Cube* cube;
Cube* wireCube;
Light* light;
Model* model;

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

ImageSourceEngine *imageSource;
ITMMainEngine *mainEngine;
ITMUChar4Image *inputRGBImage; ITMShortImage *inputRawDepthImage;
void processFrame();

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
  //do_movement();

  processFrame();
  
  // set pose of opengl camera from infinitam
  ITMPose *sensor_pose = mainEngine->GetTrackingState()->pose_d;
  Matrix4f transform = sensor_pose->GetM();
  mat4 camera_pose;
  camera_pose = make_mat4(transform.getValues());
  
  camera->SetTransformationMatrix(camera_pose);

  // fix pose of camera for opengl coordinate system
  quat rot = camera->GetRotation();
  rot.x = -rot.x;

  vec3 pos = camera->GetPosition();
  pos.y *= -1.0f;
  pos.z *= -1.0f;

  camera->SetPosition(pos);
  camera->SetRotation(rot);

  
  /*
  quat camRot = camera->GetRotation();
  //vec3 euler(-pitch(camRot), yaw(camRot), roll(camRot));
  // quat u_camRot(euler);
  camera->SetRotation(u_camRot);
  */

  light->SetPosition(vec3(1.0f + sin(glfwGetTime()) * 2.0f,
                          sin(glfwGetTime() / 2.0f) * 1.0f + 3,
                          0.0f));

  // rotate around axis
<<<<<<< HEAD
  vec3 EulerAngles(-(GLfloat)glfwGetTime(), 45, 0);
  cube->SetRotation(quat(EulerAngles));
=======
  //vec3 EulerAngles(-(GLfloat)glfwGetTime(), 45, 0);
  //cube->SetRotation(quat(EulerAngles));
  //cube1->SetRotation(quat(EulerAngles));
>>>>>>> 5df4ef7... Add necessary dependencies for using as an InfiniTAM sub project. OpenGL camera pose set by infinitam.
}

int main(int argc, char * argv[]) {

  imageSource = new OpenNIEngine("", NULL);

  if (imageSource->getDepthImageSize().x == 0) {
    delete imageSource;
    imageSource = NULL;
    cout << "Error: OpenNI device not found\n";
    return 0;
  }

  inputRGBImage = new ITMUChar4Image(imageSource->getRGBImageSize(), true, true);
  inputRawDepthImage = new ITMShortImage(imageSource->getDepthImageSize(), true, true);

  ITMLibSettings *internalSettings = new ITMLibSettings();
  mainEngine = new ITMMainEngine(internalSettings, &imageSource->calib, imageSource->getRGBImageSize(), imageSource->getDepthImageSize());

  Engine::init(argc, argv);

  // todo: not this
  auto glfw_context = dynamic_cast<GLFW3Context*>(Engine::context()); 
  glfw_context->setKeyCallBack(&key_callback);
  glfw_context->setCursorPosCallback(&mouse_callback);

  glfw_context->setClearColor(vec3(0.0f, 0.0f, 0.0f));

  Scene* scene = Engine::activeScene();
<<<<<<< HEAD
  camera = new Camera(vec3(0.0f, 0.0f, 3.0f));
=======
  camera = new ARCamera(vec3(0.0f, 0.0f, 3.0f));

>>>>>>> 5df4ef7... Add necessary dependencies for using as an InfiniTAM sub project. OpenGL camera pose set by infinitam.
  scene->setCamera(camera);

  light = new Light();
  light->SetPosition(vec3(0.0f, 3.0f, -2.0f));

  cube = new Cube();
  cube->SetPosition(vec3(-1.0f, 1.5f, 2.0f));
  cube->setColor(vec3(0.2f, 0.2f, 0.6f));


  Cube *floor = new Cube();
  floor->setColor(vec3(0.3f, 0.3f, 0.35f));
  floor->SetScale(vec3(20.0f, .2f, 20.0f));
  floor->SetPosition(vec3(0, -0.2f, 0));

  wireCube = new Cube();
  wireCube->setShader(Shader("Shaders/default.vert", "Shaders/default.frag"));
  wireCube->SetPosition(vec3(-1.0f, 0.4f, -3.0f));
  wireCube->setColor(vec3(0.9f, 0.1f, .45f));
  wireCube->setWireframe(true);
  wireCube->SetParent(cube);

  // create model from obj file
  model = new Model("nanosuit/nanosuit.obj");
  model->SetScale(vec3(0.25f, 0.25f, 0.25f));
  model->SetPosition(vec3(0, 0, -1.5f));

  // add objects to scene
  scene->add(floor);
  scene->add(model);
  scene->add(cube);
  scene->add(light);

  Engine::startMainLoop(&updateLoop);

  delete mainEngine;
  delete internalSettings;
  delete imageSource;
  delete inputRGBImage;
  delete inputRawDepthImage;
}


void processFrame()
{
  if (!imageSource->hasMoreImages()) return;
  imageSource->getImages(inputRGBImage, inputRawDepthImage);
  mainEngine->ProcessFrame(inputRGBImage, inputRawDepthImage);
  ITMSafeCall(cudaThreadSynchronize());
}



/*
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
*/


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
  //camera->ProcessMouseMovement(xoffset, yoffset);
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
