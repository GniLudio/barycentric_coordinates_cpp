#pragma once

// Include ImGui
#include <imgui.h>

// Include glad
// must be included before glfw3
#include <glad/glad.h>

// Include GLFW/OpenGL:
#include <GLFW/glfw3.h>

class Window
{
public:
	/**
	 * The constructor.
	 * @param title The window title.
	 */
	Window(char* title);

	/**
	 * The destructor.
	 */
	virtual ~Window(void);

	/**
	 * Starts rendering.
	 */
	void start(void);

	/**
	 * Gets the window width;
	 */
	int get_width(void) const;

	/**
	 * Gets the window height;
	 */
	int get_height(void) const;
protected:
	/**
	 * The GLFW window.
	 */
	GLFWwindow* window;

	/**
	 * The update function.
	 * Calls once every frame.
	 */
	virtual void update(void);
};