
#include "CircleDrawer.h"

CircleDrawer::CircleDrawer()
	: Shader("circle.vert", "circle.frag")
{
    // Generate VAO:
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate VBO:
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // get the attribute handles
    const GLint offset_attr = glGetAttribLocation(shaderProgram, "offset");

    // Link the VBO to the VAO:
    glVertexAttribPointer(offset_attr, 4, GL_FLOAT, GL_FALSE, sizeof(Vec4f), 0);
    glEnableVertexAttribArray(offset_attr);

    // Unbind the buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CircleDrawer::~CircleDrawer()
{
    // Assume that vao / vbo were generated in every case:
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void CircleDrawer::draw(Vec4f position, float radius, Vec4f color, Mat4f model_matrix, bool filled, float edge_thickness) const
{
    draw(position, radius, color, color, model_matrix, filled, edge_thickness);

}

void CircleDrawer::draw(Vec4f position, float radius, Vec4f inner_color, Vec4f outer_color, Mat4f model_matrix,
	bool filled, float edge_thickness) const
{
    bind();

    // set the uniforms
    setUniform("model_matrix", model_matrix);
    setUniform("position", position, 4);
    setUniform("radius", radius);
    setUniform("inner_color", inner_color);
    setUniform("outer_color", outer_color);
    setUniform("filled", filled);
    setUniform("edge_thickness", edge_thickness);

    // upload the data
    const Vec4f data[6] = {
        Vec4f(-radius, -radius, 0, 0), // bottom left
        Vec4f(-radius, radius,0,0), // top left
        Vec4f(radius, radius, 0,0), // top right
        Vec4f(-radius, -radius, 0,0), // bottom left
        Vec4f(radius, radius,0,0), // top right
        Vec4f(radius, -radius, 0,0), // bottom right
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    // enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // draw the circle
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 2);

    // disable blending
    glDisable(GL_BLEND);
}
