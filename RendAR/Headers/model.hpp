#pragma once
#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace RendAR {
  class Model : public Object {
  public:
    Model(std::string path)
    {
      loadModel(path);
    }

    void render(glm::mat4& view, glm::mat4& proj) override;

  protected:
    std::vector<Mesh*> meshes_;
    std::string directory_;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

  };
}
