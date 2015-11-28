#include "glfw3_context.hpp"

namespace RendAR {

  GLFW3Context::GLFW3Context(int width, int height) 
    : width_(width), height_(height)
  {}

  GLFW3Context::GLFW3Context()
  {}

  GLFW3Context::~GLFW3Context() 
  {}

  bool GLFW3Context::init(int &argc, char **argv)
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(width_, height_, "OpenGL", nullptr, nullptr);

    if (window_ == nullptr) {
      fprintf(stderr, "Failed to Create OpenGL Context");
      return 0;
    }
    return 1;
  }

  void GLFW3Context::showWindow()
  {
    glfwMakeContextCurrent(window_);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
  }


  void GLFW3Context::mainLoop()
  {
    while (glfwWindowShouldClose(window_) == false) {
      if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);

      glClearColor(0.50f, 0.25f, 0.6f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      Engine::update();
      Engine::render();
    }
    glfwTerminate();
  }


  void GLFW3Context::swapBuffers()
  {
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}
