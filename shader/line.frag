#version 330

// The input variables
in vec4 vertex_color;

// The output variables
out vec4 fragment_color;

void main()
{
	fragment_color = vertex_color;
}