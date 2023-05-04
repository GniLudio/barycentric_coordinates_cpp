#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec2 window_size;
uniform vec2 circle_position;

uniform vec4 circle_color;
uniform bool circle_filled;
uniform float circle_radius;
uniform float circle_edge_thickness;

// The input variables
in vec2 gl_FragCoord;

// The output variables
out vec4 fragment_color;

float distanceToCenter() {
	
	vec2 fragment_position = gl_FragCoord - window_size / 2;
	float d = abs(circle_position.x * 2 - fragment_position.x);
	return sqrt(d * d) / 100;
}

void main()
{

	vec2 fragment_position = gl_FragCoord - window_size / 2;
	float d = distance(circle_position, fragment_position);
	fragment_color = vec4(1, 0,0,1);
	fragment_color.a = d > circle_radius ? 0 : 1;
}