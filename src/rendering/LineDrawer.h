#pragma once
#include "Shader.h"
#include "glad/glad.h"
#include "math/Mat4f.h"
#include "math/Vec4f.h"

/**
 * \brief A line drawer.
 */
class LineDrawer : protected Shader
{
public:
	/**
	 * \brief The constructor.
	 */
	explicit LineDrawer(void);

	/**
	 * \brief The destructor.
	 */
	~LineDrawer(void);

	/**
	 * \brief Draws a line.
	 * \param start_position The start position. 
	 * \param end_position The end position.
	 * \param color The line color.
	 * \param model_matrix The model matrix.
	 */
	void draw(Vec4f start_position, Vec4f end_position, Vec4f color, Mat4f model_matrix) const;

	/**
	 * \brief Draws a line with a color gradient.
	 * \param start_position The start position.
	 * \param end_position The end position.
	 * \param start_color The start color.
	 * \param end_color The end color.
	 * \param model_matrix The model matrix.
	 */
	void draw(Vec4f start_position, Vec4f end_position, Vec4f start_color, Vec4f end_color, Mat4f model_matrix) const;

protected:
	// Pointer to Vertex Array Object (on GPU):
	GLuint vao = 0;

	// Pointer to vertex buffer:
	GLuint vbo = 0;
};
