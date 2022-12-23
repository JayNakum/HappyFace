#pragma once

#include "Renderer.h"

#include "Platform/Window.h"

#include "Components/Scene.h"

namespace Happy {
	class Application
	{
	public:
		Application();
		void go();

	protected:
		void loadScene(Scene* scene);

	private:
		std::string title = "learnopengl.com"; // Thank You https://learnopengl.com
		void terminate();
		Scene* m_scene = nullptr;
		Renderer m_renderer;
		Window m_window;
	};
}
