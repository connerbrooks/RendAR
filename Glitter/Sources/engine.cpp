#include "engine.hpp"

namespace RendAR
{
  Engine* Engine::instance = nullptr;

  Engine::Engine(int& argc, char** argv)
    : context_(new GLFW3Context())
  {
    instance = this;
    context_->init(argc, argv);
    context_->showWindow();
    createScene("default");
  }

  void Engine::startMainLoop(void (*updateLoop)())
  {
    instance->context_->mainLoop(updateLoop);
  }

  void Engine::update()
  {
    // update scene
  }

  void Engine::render()
  {
    instance->scene_->render();
    instance->context_->swapBuffers();
  }

  Context* Engine::context(){
    return instance->context_;
  }

  void
  Engine::init(int& argc, char **argv)
  {
    assert(instance == nullptr);
    new Engine(argc, argv);
  }

  Scene*
  Engine::createScene(const std::string &name)
  {
    return instance->scene_ = new Scene(name);
  }

  Scene*
  Engine::activeScene()
  {
    return instance->scene_;
  }
}
