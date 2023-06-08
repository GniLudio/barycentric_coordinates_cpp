#include "LineDrawer.h"

LineDrawer::LineDrawer() : Shader("line.vert", "line.frag")
{
	// Generate VAO:
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate VBO:
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// get the attribute handles
	const GLint position_attr = glGetAttribLocation(shaderProgram, "position");
	const GLint color_attr = glGetAttribLocation(shaderProgram, "color");

	// Link the VBO to the VAO:
	// Layout: Start Position, Start Color, End Position, End Color
	glVertexAttribPointer(position_attr, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec4f), 0);
	glEnableVertexAttribArray(position_attr);
	glVertexAttribPointer(color_attr, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec4f), (void*)sizeof(Vec4f));
	glEnableVertexAttribArray(color_attr);

	// Unbind the buffers:
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

LineDrawer::~LineDrawer()
{
	if ((*numOfCopies) - 1 > 0) return;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void LineDrawer::draw(Vec4f start_position, Vec4f end_position, Vec4f color, Mat4f model_matrix) const
{
	draw(start_position, end_position, color, color, model_matrix);
}

void LineDrawer::draw(Vec4f start_position, Vec4f end_position, Vec4f start_color, Vec4f end_color, Mat4f model_matrix) const
{
	bind();

	// sets the model matrix
	setUniform("model_matrix", model_matrix);

	// uploads the data to the vbo
	const Vec4f data[4] = { start_position, start_color, end_position, end_color };
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	// Draw the line
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
}
