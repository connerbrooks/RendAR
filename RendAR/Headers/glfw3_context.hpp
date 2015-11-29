#pragma once
#include "context.hpp"
#include "engine.hpp"

#include <GLFW/glfw3.h>

namespace RendAR {
  class GLFW3Context : public Context {
  public:
    GLFW3Context();
    virtual ~GLFW3Context();
    virtual bool init(int &argc, char **argv, const ContextConfig& config) override;
    virtual bool showWindow() override;
    virtual void mainLoop(void (*updateLoop)()) override;
    virtual void swapBuffers() override;

    void setKeyCallBack(void (*cb)(GLFWwindow*, int, int, int, int));
    void setCursorPosCallback(void (*cb)(GLFWwindow *, double, double));

  private:
    GLFWwindow *window_;
  };
}
