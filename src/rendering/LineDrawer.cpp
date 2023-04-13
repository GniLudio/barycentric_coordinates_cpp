#include "LineDrawer.h"

LineDrawer::LineDrawer()
	: shader("line.vert", "line.frag")
{
	// Generate VAO:
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate VBO:
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// get the attribute handles
	GLint positionAttr = glGetAttribLocation(shader.shaderProgram, "position");
	GLint colorAttr = glGetAttribLocation(shader.shaderProgram, "color");

	// Link the VBO to the VAO:
	// Layout: Start Position, Start Color, End Position, End Color
	glVertexAttribPointer(positionAttr, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec4f), 0);
	glEnableVertexAttribArray(positionAttr);
	glVertexAttribPointer(colorAttr, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec4f), (void*)sizeof(Vec4f));
	glEnableVertexAttribArray(colorAttr);

	// Unbind the buffers:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

LineDrawer::~LineDrawer()
{
	// Assume that vao / vbo were generated in every case:
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void LineDrawer::draw(Vec4f startPosition, Vec4f endPosition, Vec4f color, Mat4f modelMatrix) const
{
	draw(startPosition, endPosition, color, color, modelMatrix);
}

void LineDrawer::draw(Vec4f startPosition, Vec4f endPosition, Vec4f startColor, Vec4f endColor, Mat4f modelMatrix) const
{
	shader.bind();

	// sets the model matrix
	shader.setUniform("modelMatrix", modelMatrix);

	// uploads the data to the vbo
	const Vec4f data[4] = { startPosition, startColor, endPosition, endColor };
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	// Draw the line
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
}
