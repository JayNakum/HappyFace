#pragma once

#include "GLShaderProgram.h"

#include "Scene.h"
#include "Model.h"
#include "Mesh.h"

#include <unordered_map>

class Renderer
{
public:
	void init(const std::pair<int, int>& viewport);
	void update();
	
	void renderScene(Scene& scene);
	void renderModel(const Model& model, const GLShaderProgram& shader);
	void renderMesh(const Mesh& mesh, const GLShaderProgram& shader);

	void shutdown();
private:
	void defaultGLSettings() const;
	// void compileShaders();

	unsigned int m_viewportWidth, m_viewportHeight;
	std::unordered_map<const char*, GLShaderProgram> m_shaderCache;
};
