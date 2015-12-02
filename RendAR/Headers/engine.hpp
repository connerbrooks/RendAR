#pragma once
#include "glfw3_context.hpp"
#include "scene.hpp"
#include "object.hpp"

#include <string>

namespace RendAR
{
  class Engine {
  public:
    ~Engine();
    static void init(int& argc, char **argv, const ContextConfig& config = ContextConfig::plain);
    static void cleanUp();
    static Context* context();
    static Scene* createScene(const std::string &name);
    static Scene* activeScene();
    static void startMainLoop(void (*updateLoop)());
    static void update();
    static void render();

  private:
    static Engine* instance;
    Engine(int& argc, char** argv, const ContextConfig& config = ContextConfig::plain);
    Context *context_ = nullptr;
    Scene *scene_ = nullptr;
  };
}
