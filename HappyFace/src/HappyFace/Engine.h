#pragma once

#include "Renderer.h"
#include "Window.h"

class Engine
{
public:
	Engine();
	void loadScene();
	void go();

	void terminate();
private:
	Window m_window;
	Renderer m_renderer;

};

