#pragma once

#include "Mesh.h"

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

class Model
{
public:
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<GLTexture> textures_loaded;
	bool gammaCorrection = false;
	
	Model(const std::string& path, bool gamma = false);
	void deleteModel();

	void scale(const glm::vec3& scale);
	void rotate(const float radians, const glm::vec3& axis);
	void translate(const glm::vec3& pos);
	glm::mat4 getModelMatrix() const;

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<GLTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	glm::vec3 m_scale, m_position;
	
	glm::vec3 m_axis;
	float m_radians = 0.0f;
};
