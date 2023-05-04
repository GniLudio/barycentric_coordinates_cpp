#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec2 window_size;
uniform vec2 circle_position;
//uniform float circle_radius;
//uniform vec4 circle_color;
//uniform bool circle_filled;
//uniform float circle_edge_thickness;

// The input variables
in vec2 position;

// The out variables
out vec4 gl_Position;

void main()
{
	gl_Position = model_matrix * vec4((circle_position) / window_size * 2, 0, 1) + vec4(position, 0,1);
}