#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec4 circle_position;

// The input variables
in vec4 offset;

// The out variables
out vec4 gl_Position;
out vec4 vertex_offset;

void main()
{
	gl_Position = model_matrix * (circle_position + offset);
	vertex_offset = offset;
}