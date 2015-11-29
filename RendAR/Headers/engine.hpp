#pragma once
#include "glfw3_context.hpp"
#include "scene.hpp"
#include "object.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace RendAR
{
  class Engine {
  public:
    static void init(int& argc, char **argv);
    static Scene* createScene(const std::string &name);
    static Context* context();
    static void startMainLoop(void (*updateLoop)());
    static void update();
    static void render();
    static Scene* activeScene();

  private:
    static Engine* instance;
    Engine(int& argc, char** argv);
    Context *context_ = nullptr;
    Scene *scene_ = nullptr;
  };
}
