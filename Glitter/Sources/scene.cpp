#include "scene.hpp"

#include "engine.hpp"

namespace RendAR
{
  Scene::Scene(std::string name)
    : name_(name)
  {}

  void
  Scene::add(Object* o)
  {
    objects_.push_back(o);
  }

  void
  Scene::setCamera(Camera* cam)
  {
    camera_ = cam;
  }

  void
  Scene::render()
  {
    glm::mat4 view, proj;

    //view = camera_->GetViewMatrix();
    //proj = camera_->GetViewMatrix();

    //ContextConfig config = Engine::context()->getContextConfig();
    //proj = glm::perspective(45.0f, (float)(config.width / config.height), 0.1f, 100.0f);

    for (auto o : objects_)
      o->render();
  }
}
