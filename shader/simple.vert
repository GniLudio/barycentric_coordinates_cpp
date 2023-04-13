#version 330

// The uniform variables
uniform mat4 modelMatrix;

// The input variables
in vec4 position;
in vec4 color;

// The output variables
out vec4 gl_Position;
out vec4 vertex_color;

void main()
{
	gl_Position = modelMatrix * position;
	vertex_color = color;
}