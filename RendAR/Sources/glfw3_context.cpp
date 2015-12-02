#include "glfw3_context.hpp"

namespace RendAR {

  GLFW3Context::GLFW3Context()
  {}

  GLFW3Context::~GLFW3Context()
  {}

  bool GLFW3Context::init(int &argc, char **argv, const ContextConfig& config)
  {
    config_ = config;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    return 1;
  }

  bool GLFW3Context::showWindow()
  {

    window_ = glfwCreateWindow(config_.width, config_.height, config_.name.c_str(), nullptr, nullptr);

    if (window_ == nullptr) {
      fprintf(stderr, "Failed to Create OpenGL Context");
      return 0;
    }

    glfwMakeContextCurrent(window_);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST);

    return 1;
  }


  void GLFW3Context::mainLoop(void (*updateLoop)())
  {
    while (glfwWindowShouldClose(window_) == false) {
      if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);

      glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      updateLoop();

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

  void GLFW3Context::setKeyCallBack(void (*cb)(GLFWwindow*, int, int, int, int))
  {
    glfwSetKeyCallback(window_, cb);
  }


  void GLFW3Context::setCursorPosCallback(void (*cb)(GLFWwindow *, double, double))
  {
    glfwSetCursorPosCallback(window_, cb);
  }
}
