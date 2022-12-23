#pragma once

#include <functional>
#include <array>

#include <iostream>

#include <GLFW/glfw3.h>

class Input
{
	Input() 
	{
		std::fill(m_keys.begin(), m_keys.end(), false);
		std::fill(m_prevKeys.begin(), m_prevKeys.end(), false);
	}
	~Input() = default;

public:

	float lastX = (float)m_windowWidth / 2.0;
	float lastY = (float)m_windowHeight / 2.0;
	bool firstMouse = true;

	enum Key : int{
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		TAB = GLFW_KEY_TAB,
		ESC = GLFW_KEY_ESCAPE
	};
	
	static Input& getInstance() 
	{
		static Input instance;
		return instance;
	}

	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	inline bool isKeyPressed(const std::size_t key) const noexcept 
	{
		return m_keys[key] && !m_prevKeys[key];
	}
	inline bool isKeyHeld(const std::size_t key) const noexcept 
	{
		return m_keys[key];
	}
	std::function<void(int, int, int, int)> keyPressed = [&](auto key, auto scancode, auto action, auto mode) 
	{
		if (key >= 0 && key < 1024) 
		{
			switch (action) 
			{
				case 1:
					this->m_keys[key] = true;
					break;
				case 0:
					this->m_keys[key] = false;
					break;
			}
		}
	};

	// Mouse
	inline bool isMouseMoved() const noexcept { return m_mouseMoved; }
	inline double getMouseX() const noexcept { return m_mouseX; }
	inline double getMouseY() const noexcept { return m_mouseY; }
	std::function<void(double, double)> mouseMoved = [&](auto xPos, auto yPos) 
	{
		this->m_mouseMoved = true;
		this->m_mouseX = xPos;
		this->m_mouseY = yPos;
	};

	// Window
	inline bool isWindowResized() const noexcept { return m_windowResized; }
	inline int getWindowWidth() const noexcept { return (int)m_windowWidth; }
	inline int getWindowHeight() const noexcept { return (int)m_windowHeight; }
	std::function<void(int, int)> windowResized = [&](auto width, auto height) 
	{
		this->m_windowResized = true;
		this->m_windowWidth = width;
		this->m_windowHeight = height;
	};

	void update() 
	{
		m_mouseMoved = false;
		m_windowResized = false;

		std::copy(m_keys.cbegin(), m_keys.cend(), m_prevKeys.begin());
	}

private:
	// Keyboard
	std::array<bool, 1024> m_keys;
	std::array<bool, 1024> m_prevKeys;

	// Mouse
	bool m_mouseMoved = false;
	double m_mouseX, m_mouseY;

	// Resize
	bool m_windowResized = false;
	std::size_t m_windowWidth, m_windowHeight;
};