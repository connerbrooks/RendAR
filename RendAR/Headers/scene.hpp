#pragma once
#include "object.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "context_config.hpp"

#include <string>
#include <vector>

namespace RendAR
{
  class Scene {
  public:
    Scene(std::string name);
    ~Scene();
    void add(Object* o);
    void setCamera(Camera *cam);
    Camera* getCamera();
    void render();
    std::vector<Object*> getSceneObjects();
    std::vector<Light*> getLights();
  private:
    std::string name_;
    Camera* camera_;
    std::vector<Object*> objects_;
    std::vector<Light*> lights_;
    const int MAX_LIGHTS = 4;
  };
}
