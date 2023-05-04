
#include "CircleDrawer.h"

#include <iostream>

CircleDrawer::CircleDrawer()
	: shader("circle.vert", "circle.frag")
{
    // Generate VAO:
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate VBO:
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // get the attribute handles
    GLint positionAttr = glGetAttribLocation(shader.shaderProgram, "position");

    // Link the VBO to the VAO:
    glVertexAttribPointer(positionAttr, 2, GL_FLOAT, GL_FALSE, sizeof(Vec4f), 0);
    glEnableVertexAttribArray(positionAttr);

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

void CircleDrawer::draw(Vec4f position, float radius, Vec4f color, Mat4f modelMatrix, Vec4f windowSize, bool filled, float edgeThickness) const
{
    shader.bind();

    // set the uniforms
    shader.setUniform("model_matrix", modelMatrix);
    shader.setUniform("window_size", windowSize, 2);
    shader.setUniform("circle_position", position, 2);
    shader.setUniform("circle_radius", radius);
    shader.setUniform("circle_color", color);
    shader.setUniform("circle_filled", filled);
    shader.setUniform("circle_edge_thickness", edgeThickness);

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
