#pragma once

#include "GLShaderProgram.h"
#include "Model.h"

#include <unordered_map>

class Renderer
{
public:
	void init(const std::pair<int, int>& viewport);
	void update();
	
	void render(const Mesh& mesh);
	void shutdown();
private:
	void defaultGLSettings() const;
	void compileShaders();

	unsigned int m_viewportWidth, m_viewportHeight;
	std::unordered_map<const char*, GLShaderProgram> m_shaderCache;
};
