#pragma once

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <functional>

class Model
{
public:
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<GL::Texture> textures_loaded;
	bool gammaCorrection = false;
	
	Model(const std::string& path, const std::function<void()> updateFn = []() {}, bool gamma = false);
	void deleteModel();

	void scale(const glm::vec3& scale);
	void rotate(const float angle, const glm::vec3& axis);
	void translate(const glm::vec3& pos);
	glm::mat4 getModelMatrix() const;

	std::function<void()> update;

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<GL::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f }, m_position = {0.0f, 0.0f, 0.0f};
	
	glm::vec3 m_axis = {1.0f, 1.0f, 1.0f};
	float m_radians = 0.0f;
};
