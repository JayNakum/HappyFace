#include "Scene.h"

#include "Utility/ResourceManager.h"

namespace Happy {
	Scene::Scene()
		: camera(glm::vec3(0.0f, 0.0f, 3.0f)) 
	{
		modelShader.reserve(2);
		m_shaders.reserve(2);
	}

	void Scene::deleteScene()
	{
		for (auto& model : m_models)
			model.deleteModel();
		m_models.clear();

		for (auto& shader : m_shaders)
			(shader.second).deleteProgram();
		m_shaders.clear();
	}

	void Scene::initShaders()
	{
		modelShader = { "resources/shaders/model.vs.glsl", "resources/shaders/model.fs.glsl" };
		addShader("modelShader", modelShader);
	}

	void Scene::initModels() {}

	void Scene::addModel(const Model& model)
	{
		m_models.push_back(model);
	}

	void Scene::addShader(const std::string& name, const std::vector<std::string>& shaderPaths)
	{
		m_shaders.insert({ name, ResourceManager::getInstance().loadShaderProgram(shaderPaths)});
	}
}
