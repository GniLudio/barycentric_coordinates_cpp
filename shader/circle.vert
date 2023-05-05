#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec4 window_size;
uniform vec4 circle_position;
//uniform float circle_radius;
//uniform vec4 circle_color;
//uniform bool circle_filled;
//uniform float circle_edge_thickness;

// The input variables
in vec4 position;

// The out variables
out vec4 gl_Position;

void main()
{
	gl_Position = model_matrix * (circle_position / window_size * 2) + (position / window_size * 2) * 2;
}