#pragma once
#include "object.hpp"
#include "camera.hpp"
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
    void render();

  private:
    Camera* camera_;
    std::string name_;
    std::vector<Object*> objects_;

  };
}
