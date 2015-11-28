// Local Headers
#include "glitter.hpp"
#include "engine.hpp"
#include "camera.hpp"
#include "cube.hpp"

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
  Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

  scene->setCamera(camera);

  Cube* cube = new Cube();
  Cube* cube1 = new Cube();
  cube->SetPosition(glm::vec3(-0.6f, 0.4f, -1.0f));
  cube1->SetPosition(glm::vec3(-1.0f, -0.4f, -3.0f));
  scene->add(cube);
  scene->add(cube1);

  Engine::startMainLoop();

}
