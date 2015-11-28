// Local Headers
#include "glitter.hpp"
#include "engine.hpp"
#include "camera.hpp"

// System Headers
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

using namespace RendAR;

int main(int argc, char * argv[]) {

  Engine::init(argc, argv);
  Scene* scene = Engine::activeScene();
  //Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

  //scene->setCamera(camera);

  Object* triangle = new Object();
  scene->add(triangle);

  Engine::startMainLoop();

}
