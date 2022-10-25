#pragma once

#include "Window.h"
#include "Renderer.h"

class Engine
{
public:
	Engine();
	void go();

	void loadScene();

	void terminate();
private:
	Window m_window;
	Renderer m_renderer;

};

