#pragma once

#include "Components/Model.h"
#include "Components/Camera.h"

#include "GL/ShaderProgram.h"
#include "GL/Shader.h"

#include <string>
#include <unordered_map>

namespace Happy {
	class Scene
	{
	public:
		Camera camera;
		std::vector<Model> models;

		inline GL::ShaderProgram& getShader(const std::string& name) { return shaders.at(name); }

		Scene();

		void init();

		void addModel(const Model& model);
		// TODO: void addLight();

		void deleteScene();

	protected:
		std::vector<std::string> modelShader = { "resources/shaders/model.vs.glsl", "resources/shaders/model.fs.glsl" };
		void addShader(const std::string& name, const std::vector<std::string>& shaders);

	private:
		std::unordered_map<std::string, GL::ShaderProgram> shaders;
	};
}
