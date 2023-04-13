#pragma once
#include "Shader.h"
#include "glad/glad.h"
#include "math/Mat4f.h"
#include "math/Vec4f.h"

class LineDrawer
{
public:
	/** The constructor. */
	LineDrawer();

	/** The destructor. */
	~LineDrawer();

	/** Draws a line with a color. */
	void draw(Vec4f startPosition, Vec4f endPosition, Vec4f color, Mat4f modelMatrix) const;

	/** Draws a line with a color gradient. */
	void draw(Vec4f startPosition, Vec4f endPosition, Vec4f startColor, Vec4f endColor, Mat4f modelMatrix) const;

private:
	// Pointer to Vertex Array Object (on GPU):
	GLuint vao = 0;

	// Pointer to vertex buffer:
	GLuint vbo = 0;

	// Shader to draw the lines:
	Shader shader;
};
