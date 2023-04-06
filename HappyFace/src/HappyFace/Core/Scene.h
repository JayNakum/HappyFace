#pragma once

#include "Components/Model.h"
#include "Components/Camera.h"

#include "GL/ShaderProgram.h"
#include "GL/Shader.h"

#include <unordered_map>

namespace Happy {
	class Scene
	{
	public:
		Camera camera;

		inline GL::ShaderProgram& getShader(const std::string& name) { return m_shaders.at(name); }
		inline std::vector<Model> getModels() const { return m_models; }

		Scene();
		void deleteScene();

		virtual void initShaders();
		virtual void initModels();

	protected:
		void addShader(const std::string& name, const std::vector<std::string>& shaders);
		void addModel(const Model& model);
		// TODO: void addLight();

	protected:
		std::vector<std::string> modelShader;

	private:
		std::vector<Model> m_models;
		std::unordered_map<std::string, GL::ShaderProgram> m_shaders;
	};
}
