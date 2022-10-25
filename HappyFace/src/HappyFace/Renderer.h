#pragma once
class Renderer
{
public:
	void init(const unsigned int viewportWidth, const unsigned int viewportHeight);
	void update();
	// void render();

private:
	unsigned int m_viewportWidth, m_viewportHeight;
};
