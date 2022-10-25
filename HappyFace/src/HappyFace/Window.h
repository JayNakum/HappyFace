#pragma once

#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
	Window() noexcept = default;
	void update();

	GLFWwindow* init(const std::string& title = "LearnOpenGL.com", const unsigned int width = 800, const unsigned int height = 600, const bool fullscreen = false);
	void shutdown() const;

	void swapBuffers() const;

	void enableCursor() const;
	void disableCursor() const;

	void setVsync(const bool vsync) const;

	inline unsigned int getWidth() const noexcept { return m_data.width; }
	inline unsigned int getHeight() const noexcept { return m_data.height; }

	inline bool shouldClose() const noexcept { return m_data.shouldWindowClose; }
	inline bool isCursorEnabled() const noexcept { return m_data.showCursor; }

private:
	GLFWwindow* m_window{ nullptr };

	struct WindowData {

		std::string title;
		unsigned int width;
		unsigned int height;

		bool shouldWindowClose;
		bool showCursor;
	}m_data;

};

