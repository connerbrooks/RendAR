#pragma once
#include "libplatform/libplatform.h"
#include "v8.h"


namespace RendAR
{
  class ScriptingEngine
  {
  public:
    ScriptingEngine(int &argc, char** argv);
    ~ScriptingEngine();

  private:
    v8::Platform* platform_;

  };
}
