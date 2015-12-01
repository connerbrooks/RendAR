#include "model.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace RendAR {
  void Model::render(glm::mat4& view, glm::mat4& proj)
  {
    for (auto m : meshes_)
      m->render(view, proj);
  }

  void Model::loadModel(std::string path)
  {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cout << "Error::Assimp::" << import.GetErrorString() << "\n";
      return;
    }

    directory_ = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
  }

  void Model::processNode(aiNode *node, const aiScene *scene)
  {
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes_.push_back(processMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; i++) {
      processNode(node->mChildren[i], scene);
    }
  }

  Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene)
  {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;
      glm::vec3 vec;
      vec.x = mesh->mVertices[i].x;
      vec.y = mesh->mVertices[i].y;
      vec.z = mesh->mVertices[i].z;
      vertex.Position = vec;

      vec.x = mesh->mNormals[i].x;
      vec.y = mesh->mNormals[i].y;
      vec.z = mesh->mNormals[i].z;
      vertex.Normal = vec;

      if (mesh->mTextureCoords[0]) {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.TexCoords = vec;
      }
      else
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);

      vertices.push_back(vertex);
    }


    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for(GLuint j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }


    if (mesh->mMaterialIndex >= 0) {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
      std::vector<Texture> diffuseMaps
        = loadMaterialTextures(material,
                               aiTextureType_DIFFUSE,
                               "texture_diffuse");
      textures.insert(textures.end(),
                      diffuseMaps.begin(),
                      diffuseMaps.end());
      std::vector<Texture> specularMaps
        = loadMaterialTextures(material,
                               aiTextureType_SPECULAR,
                               "texture_specular");
      textures.insert(textures.end(),
                      specularMaps.begin(),
                      specularMaps.end());

    }

    Mesh* m = new Mesh(vertices, indices, textures);
    //m->setWireframe(true);
    return m;
  }

  GLint TextureFromFile(const char* path, std::string directory);

  std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
  {
    std::vector<Texture> textures;

    for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), directory_);
      texture.type = typeName;
      texture.path = str;
      textures.push_back(texture);
    }
    return textures;
  }

  GLint TextureFromFile(const char* path, std::string directory)
  {
    //Generate texture ID and load texture data
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height,channels;
    unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    GLenum format;
    switch (channels)
    {
      case 1 : format = GL_ALPHA;     break;
      case 2 : format = GL_LUMINANCE; break;
      case 3 : format = GL_RGB;       break;
      case 4 : format = GL_RGBA;      break;
    }
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
    return textureID;
  }
}
