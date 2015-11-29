#pragma once
#include "context_config.hpp"

#include <iostream>
#include <string>

namespace RendAR
{
  class Context {
  public:
    Context();
    virtual ~Context(){};
    virtual bool init(int &argc, char **argv, const ContextConfig& config) = 0;
    virtual bool showWindow() = 0;
    virtual void mainLoop(void (*updateLoop)()) = 0;
    virtual void swapBuffers() = 0;
    ContextConfig getContextConfig();

  protected:
    ContextConfig config_;
  };
}
