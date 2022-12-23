#pragma once

#include "Renderer.h"
#include "Window.h"

#include "Scene.h"

class Engine
{
public:
	Engine();
	void go();

	void terminate();
private:
	Renderer m_renderer;
	Window m_window;
};
