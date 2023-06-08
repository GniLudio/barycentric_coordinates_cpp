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
     * @param modelMatrix The model matrix.
     * @param filled Whether the circle is filled.
     * @param edgeThickness The edge thickness for non-filled circles.
     */
    void draw(Vec4f position, float radius, Vec4f color, Mat4f modelMatrix, bool filled = true, float edgeThickness = 1) const;

    /**
     * \brief Draws a circle.
     * \param position The center position.
     * \param radius The radius.
     * \param inner_color The inner color.
     * \param outer_color The outer color.
     * \param model_matrix The model matrix.
     * \param filled Whether the circle is filled.
     * \param edge_thickness The edge thickness. (if not filled)
     */
    void draw(Vec4f position, float radius, Vec4f inner_color, Vec4f outer_color, Mat4f model_matrix, bool filled = true, float edge_thickness = 1.f) const;
private:
    // Pointer to Vertex Array Object (on GPU):
    GLuint vao = 0;

    // Pointer to vertex buffer:
    GLuint vbo = 0;

    // Shader to draw the lines:
    Shader shader;
};
