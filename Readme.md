RendAR
======

![demo gif](https://raw.githubusercontent.com/connerbrooks/RendAR/gh-pages/rendar.gif)

Getting Started
---------------
Like [Glitter](http://polytonic.github.io/Glitter/) RendAR only depends on
[cmake](http://www.cmake.org/download/), which generates projects or makefiles
for your platform. Clone the repository recursively

```bash
git clone --recursive https://github.com/connerbrooks/RendAR.git
cd RendAR
cd Build
```

Generate a project or Makefile for your platform:

```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 14" ..
cmake -G "Visual Studio 14 Win64" ..
...
```

Compile and run, the test project will create some objects and a camera.
The camera can be controlled with `WASD` and the mouse.


Usage
-----

```
#include "rendar.h"

using namespace RendAR;
using namespace glm;

Cube *cube;

void
updateLoop()
{
  // rotate cube
  vec3 EulerAngles(-(GLfloat)glfwGetTime(), 45, 0);
  cube->SetRotation(quat(EulerAngles));
}

int
main(int argc, char *argv[])
{
  Engine::init(argc, argv);
  Scene *scene = Engine::activeScene();
  Camera *camera = new Camera(vec3(0.0, 0.0, 3.0));
  scene->setCamera(camera);

  cube = new Cube();
  cube1->SetPosition(glm::vec3(-1.0f, -0.4f, -3.0f));

  scene->add(cube);

  Engine::startMainLoop(&updateLoop);
}
```
