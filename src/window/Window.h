#pragma once

// Include ImGui
#include <imgui.h>

// Include glad
// must be included before glfw3
#include <glad/glad.h>

// Include GLFW/OpenGL:
#include <GLFW/glfw3.h>

// Type for ImGui styles:
typedef void (*ImGuiStyleFunction)(ImGuiStyle*);

class Window
{
public:
	/**
	 * The GLFW window.
	 */
	GLFWwindow* window;

	/**
	 * The constructor.
	 * @param title The window title.
	 * @param width The initial window width.
	 * @param height The initial window height.
	 * @param fontSize The font size.
	 * @param imGuiStyle The ImGui style.
	 */
	Window(char* title, int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imGuiStyle = ImGui::StyleColorsClassic);

	/**
	 * The destructor.
	 */
	~Window(void);

	/**
	 * Starts rendering.
	 */
	void Start(void);

	/**
	 * The Update function.
	 * Calls once every frame.
	 */
	virtual void Update(void);

	/**
	 * Gets the window width;
	 */
	int getWidth(void) const;

	/**
	 * Gets the window height;
	 */
	int getHeight(void) const;
};