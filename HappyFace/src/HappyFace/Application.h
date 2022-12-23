#pragma once

#include "Renderer.h"
#include "Window.h"

#include "Scene.h"

class Application
{
public:
	Application();
	void go();

protected:
	void loadScene(Scene* scene);

private:
	void terminate();
	Scene* m_scene = nullptr;
	Renderer m_renderer;
	Window m_window;
};
