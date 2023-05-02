#version 330

// The uniform variables
uniform mat4 model_matrix;
uniform vec2 window_size;

// The input variables
in vec2 position;

// The out variables
out vec4 gl_Position;

void main()
{
	gl_Position = vec4(position / window_size * 2,0,1);
}