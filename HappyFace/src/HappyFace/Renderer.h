#pragma once

#include "Entity.h"
#include "GLShaderProgram.h"

#include <unordered_map>

class Renderer
{
public:
	void init(const std::pair<int, int>& viewport);
	void update();
	
	void render(const Entity& entity);
	void shutdown();
private:
	void defaultGLSettings() const;
	void compileShaders();

	unsigned int m_viewportWidth, m_viewportHeight;
	std::unordered_map<const char*, GLShaderProgram> m_shaderCache;
};
