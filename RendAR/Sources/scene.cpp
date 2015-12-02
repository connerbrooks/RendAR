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
  Scene::add(Light* l)
  {
    lights_.push_back(dynamic_cast<Light *>(l));
  }

  void
  Scene::add(Model* model)
  {
    models_.push_back(model);
  }

  void
  Scene::setCamera(Camera* cam)
  {
    camera_ = cam;
  }

  Camera*
  Scene::getCamera()
  {
    return camera_;
  }

  std::vector<Object*>
  Scene::getObjects()
  {
    return objects_;
  }

  std::vector<Light*>
  Scene::getLights()
  {
    return lights_;
  }

  void
  Scene::render()
  {
    glm::mat4 view, proj;

    if (camera_) {
      view = camera_->GetViewMatrix();
    }

    ContextConfig config = Engine::context()->getContextConfig();
    proj = glm::perspective(45.0f,
                            ((GLfloat)config.width / (GLfloat)config.height),
                            0.1f, 100.0f);

    for (auto o : objects_)
      o->render(view, proj);

    for (auto l : lights_)
      if (lights_.size() < MAX_LIGHTS)
        l->render(view, proj);

    for (auto m : models_)
      m->render(view, proj);

  }

}
