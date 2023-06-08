#version 330

// The transformation matrix
uniform mat4 model_matrix;

// The input variables
in vec4 position;
in vec4 color;

// The out variables
out vec4 gl_Position;
out vec4 vertex_color;

void main()
{
	gl_Position = model_matrix * position;
	vertex_color = color;
}