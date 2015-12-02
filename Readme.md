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

Using InfiniTAM with RendAR
---------------------------
Clone InfiniTAM and add RendAR as a subproject:

```bash
git clone https://github.com/victorprad/InfiniTAM.git
cd InfiniTAM
git clone https://github.com/connerbrooks/RendAR.git
```

Build InfiniTAM with cmake.

Add RendAR as a sub directory in `InfiniTAM/InfiniTAM/CMakeLists.txt` under the other sub directory additions
```
add_subdirectory(Engine)
add_subdirectory(RendAR)
```

 Reconfigure and generate with Cmake, then build the RendAR project.

On Windows it may be necessary to grab `C:\Program Files\OpenNI2\Redist` and paste it in the output directory.
If there are issues with tracking, you may need to make the changes described [here](http://com.occipital.openni.s3.amazonaws.com/Structure%20Sensor%20OpenNI2%20Quick%20Start%20Guide.pdf).


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
