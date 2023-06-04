#version 330

// The uniform variables
uniform vec4 circle_color;
uniform bool circle_filled;
uniform float circle_radius;
uniform float circle_edge_thickness;

// The input variables
in vec4 vertex_offset;

// The output variables
out vec4 fragment_color;

void main()
{
	// calculates the distance from the center
	float d = length(vertex_offset);
	// on the edge
	if ((d / circle_radius) <= 1 && (circle_radius - d) < circle_edge_thickness)
		fragment_color = circle_color;
	// inside
	else if ((d / circle_radius) <= 1 && circle_filled)
		fragment_color = circle_color;
	else
		fragment_color = vec4(0,0,0,0);
}