#pragma once

#include "GL/ShaderProgram.h"

#include "Components/Scene.h"
#include "Components/Model.h"
#include "Components/Mesh.h"

#include <unordered_map>

class Renderer
{
public:
	void init(const std::pair<int, int>& viewport);
	void update();
	
	void renderScene(Happy::Scene& scene);
	void renderModel(const Model& model, const GL::ShaderProgram& shader);
	void renderMesh(const Mesh& mesh, const GL::ShaderProgram& shader);

	void shutdown();
private:
	void defaultGLSettings() const;
	// void compileShaders();

	unsigned int m_viewportWidth, m_viewportHeight;
	std::unordered_map<const char*, GL::ShaderProgram> m_shaderCache;
};
