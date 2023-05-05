#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec4 window_size;
uniform vec4 circle_position;
uniform vec4 circle_color;
uniform bool circle_filled;
uniform float circle_radius;
uniform float circle_edge_thickness;

// The input variables
in vec4 gl_FragCoord;

// The output variables
out vec4 fragment_color;

void main()
{

	vec4 fragment_position = gl_FragCoord - window_size / 2;
	float d = distance(fragment_position.xy, (model_matrix * circle_position).xy);
	
	fragment_color = vec4(d / circle_radius,0,0,1);
}