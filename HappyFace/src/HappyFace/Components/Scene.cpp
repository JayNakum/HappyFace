#include "Scene.h"

#include "Utility/ResourceManager.h"

Scene::Scene()
	: camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

void Scene::addModel(const Model& model)
{
	models.push_back(model);
}

void Scene::init()
{
	addShader("modelShader", modelShader);
}

void Scene::addShader(const std::string& name, const std::vector<std::string>& shaderPaths)
{
	GL::ShaderProgram shaderProgram;
	std::vector<GL::Shader> shadersList;

	for (auto& path : shaderPaths)
	{
		GL::Shader shader = ResourceManager::getInstance().loadShader(path);
		shadersList.push_back(shader);
		shaderProgram.attach(shader.getID());
	}

	shaderProgram.linkProgram();
	shaders.insert({ name, shaderProgram });

	for (auto& shader : shadersList)
		shader.deleteShader();
}

void Scene::deleteScene()
{
	for (auto& model : models)
		model.deleteModel();
	models.clear();

	for (auto& shader : shaders)
		(shader.second).deleteProgram();
	shaders.clear();
}
