#pragma once
#include "object.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "context_config.hpp"
#include "model.hpp"

#include <string>
#include <vector>

namespace RendAR
{
  class Scene {
  public:
    Scene(std::string name);
    ~Scene();
    void add(Object* o);
    void add(Light* l);
    void add(Model* l);
    void setCamera(Camera *cam);
    Camera* getCamera();
    void render();
    std::vector<Object*> getObjects();
    std::vector<Light*> getLights();
  private:
    std::string name_;
    Camera* camera_;
    std::vector<Object*> objects_;
    std::vector<Light*> lights_;
    std::vector<Model*> models_;
    const int MAX_LIGHTS = 4;
  };
}
