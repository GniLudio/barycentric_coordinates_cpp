#pragma once
#include "Shader.h"
#include "glad/glad.h"
#include "math/Vec4f.h"

class CircleDrawer
{
public:
    /** The constructor. */
    CircleDrawer();

    /** The destructor. */
    ~CircleDrawer();

    /**
     * Draws a circle.
     * @param position The center position.
     * @param radius The radius.
     * @param color The color.
     * @param windowSize The window size.
     * @param filled Whether the circle is filled.
     * @param edgeThickness The edge thickness for non-filled circles.
     */
    void draw(Vec4f position, float radius, Vec4f color, Vec4f windowSize, bool filled = true, float edgeThickness = 1) const;
private:
    // Pointer to Vertex Array Object (on GPU):
    GLuint vao = 0;

    // Pointer to vertex buffer:
    GLuint vbo = 0;

    // Shader to draw the lines:
    Shader shader;
};
