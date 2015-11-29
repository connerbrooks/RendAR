#pragma once
#include <string>

namespace RendAR
{
  struct ContextConfig {
    std::string name = "Kick";
    unsigned int width = 800;
    unsigned int height = 600;

    static const ContextConfig plain;
  };
}
