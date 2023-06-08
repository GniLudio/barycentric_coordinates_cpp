#version 330

// The uniform variables
uniform float radius;
uniform vec4 inner_color;
uniform vec4 outer_color;
uniform bool filled;
uniform float edge_thickness;

// The input variables
in vec4 vertex_offset;

// The output variables
out vec4 fragment_color;

void main()
{
	// calculates the distance from the center
	float d = length(vertex_offset);
	vec4 color = mix(inner_color, outer_color, d / radius);
	// on the edge
	if ((d / radius) <= 1 && (radius - d) < edge_thickness)
		fragment_color = color;
	// inside
	else if ((d / radius) <= 1 && filled)
		fragment_color = color;
	// outside
	else
		fragment_color = vec4(0,0,0,0);
}