#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec2 window_size;
uniform vec2 circle_position;
uniform float circle_radius;
uniform vec4 circle_color;
uniform bool circle_filled;
uniform float circle_edge_thickness;

// The input variables
in vec2 gl_FragCoord;

// The output variables
out vec4 fragment_color;

void main()
{
	vec2 fragment_position = gl_FragCoord - window_size / 2;
	float d = distance(circle_position, fragment_position);
	
	if (d<= circle_radius && ((circle_radius - d) <= circle_edge_thickness)) {
		fragment_color = circle_color;
	}
	else if (d <= circle_radius && circle_filled) {
		fragment_color = circle_color;
	}
}