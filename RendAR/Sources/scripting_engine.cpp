#include "scripting_engine.hpp"
#include <iostream>

namespace RendAR
{
  ScriptingEngine::ScriptingEngine(int &argc, char** argv)
  {
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    platform_ = v8::platform::CreateDefaultPlatform();

    v8::V8::InitializePlatform(platform_);
    v8::V8::Initialize();

    // test test test
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    v8::Isolate* isolate = v8::Isolate::New(create_params);
    {
      v8::Isolate::Scope isolate_scope(isolate);

      v8::HandleScope handle_scope(isolate);

      v8::Local<v8::Context> context = v8::Context::New(isolate);

      v8::Context::Scope context_scope(context);

      v8::Local<v8::String> source =
        v8::String::NewFromUtf8(isolate, "'Hello' + ', World!'", v8::NewStringType::kNormal).ToLocalChecked();

      v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();

      v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

      v8::String::Utf8Value utf8(result);

      std::cout << *utf8 << std::endl;
    }
    isolate->Dispose();
  }

  ScriptingEngine::~ScriptingEngine()
  {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete platform_;
  }

}
