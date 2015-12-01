#pragma once
#include "context_config.hpp"
#include "glm/common.hpp"

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
    void setClearColor(const glm::vec3& color);

  protected:
    ContextConfig config_;
    glm::vec3 clear_color_ = glm::vec3(0.2f, 0.3f, 0.3f);
  };
}
