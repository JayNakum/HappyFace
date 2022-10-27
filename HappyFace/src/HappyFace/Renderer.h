#pragma once

#include "Entity.h"

class Renderer
{
public:
	void init(const unsigned int viewportWidth, const unsigned int viewportHeight);
	void update();
	
	void render(const Entity& entity);

private:
	unsigned int m_viewportWidth, m_viewportHeight;
};
