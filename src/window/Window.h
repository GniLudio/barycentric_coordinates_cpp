#pragma once

// Include glad
// must be included before glfw3
#include <glad/glad.h>

// Include GLFW/OpenGL:
#include <GLFW/glfw3.h>

/**
 * \brief A window.
 */
class Window
{
public:
	/**
	 * \brief The constructor.
	 * \param title The title.
	 */
	explicit Window(const char* title);

	/**
	 * \brief The destructor.
	 */
	~Window(void);

	/**
	 * \brief Starts rendering.
	 */
	void start(void);

	/**
	 * \brief Returns the window width.
	 * \return The window width.
	 */
	int get_width(void) const;

	/**
	 * \brief Returns the window height.
	 * \return The window height.
	 */
	int get_height(void) const;
protected:
	/**
	 * \brief The glfw window.
	 */
	GLFWwindow* window;

	/**
	 * \brief The update method. (Called each frame)
	 */
	virtual void update(void);
};