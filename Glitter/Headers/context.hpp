#pragma once

#include <iostream>
#include <string>
#include "glm/glm.hpp"

namespace RendAR
{
  class Context {
  public:
    Context();
    virtual ~Context(){};
    virtual bool init(int &argc, char **argv) = 0;
    virtual void showWindow() = 0;
    virtual void mainLoop() = 0;
    virtual void swapBuffers() = 0;
  };
}
