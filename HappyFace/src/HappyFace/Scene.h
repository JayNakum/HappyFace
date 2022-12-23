#pragma once

#include "GLShaderProgram.h"
#include "GLShader.h"

#include "Model.h"
#include "Camera.h"

#include <string>
#include <unordered_map>

class Scene 
{
public:
	Camera camera;
	std::vector<Model> models;
	
	inline GLShaderProgram& getShader(const std::string& name) { return shaders.at(name); }

	Scene();

	void init();
	void addShader(const std::string& name, const std::vector<std::string>& shaders);
	void addModel(const Model& model);
	void deleteScene();

protected:
	std::vector<std::string> modelShader = { "resources/shaders/model.vs.glsl", "resources/shaders/model.fs.glsl" };

private:
	std::unordered_map<std::string, GLShaderProgram> shaders;
};
