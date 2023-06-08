
#include "Shader.h"

// Loading files in C++:
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

// Include OpenGL3.3 Core functions:
#include <glad/glad.h>


Shader::Shader(const char* vertex_shader, const char* fragment_shader, const char* source_dir)
	: num_of_copies(new int(1))
{
    const std::string s_source_dir = std::string(source_dir);
	const std::string vertex_shader_path = s_source_dir + vertex_shader;
	const std::string fragment_shader_path = s_source_dir + fragment_shader;

    // Load vertex shader source as string:
    std::ifstream ifs(vertex_shader_path);
    std::string vertexShaderSourceString(std::istreambuf_iterator<char>{ifs}, {});
    const char* vertexShaderSource = vertexShaderSourceString.c_str();
    ifs.close();

    // Load fragment shader source as string:
    ifs = std::ifstream(fragment_shader_path);
    std::string fragmentShaderSourceString(std::istreambuf_iterator<char>{ifs}, {});
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
    ifs.close();

    // Create temporary pointers to the compiled vertex and fragment shader:
    unsigned int t_vertex_shader, t_fragment_shader;

    // Upload VERTEX SHADER source code to GPU and compile it:
    t_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(t_vertex_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(t_vertex_shader);

    // Check if compilation was successful, otherwise print error:
    int success;
    glGetShaderiv(t_vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(t_vertex_shader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader Compilation failed:\n" << "File: " << vertex_shader_path << infoLog << std::endl;
    }

    // Upload FRAGMENT SHADER source code to GPU and compile it:
    t_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(t_fragment_shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(t_fragment_shader);

    // Check if compilation was successful, otherwise print error to console:
    glGetShaderiv(t_fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(t_fragment_shader, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Compilation failed:\n" << "File: " << fragment_shader_path << infoLog << std::endl;
    }

    // Finally create the shader program which contains both vertex and fragment shader:
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, t_vertex_shader);
    glAttachShader(shaderProgram, t_fragment_shader);
    glLinkProgram(shaderProgram);

    // Check if linking of shaders was successful, otherwise print error to console:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << " (" << vertex_shader_path << ", " << fragment_shader_path << ")" << std::endl;
    }

    // After shaders were linked to a shader program, we don't need the
    // compiled shaders anymore to run the shader program, so we can delete
    // it on the GPU:
    glDeleteShader(t_vertex_shader);
    glDeleteShader(t_fragment_shader);

    if (success)
        initialized = true;
}

Shader::Shader(const Shader& shader)
	: shaderProgram(shader.shaderProgram), initialized(shader.initialized), num_of_copies(shader.num_of_copies)
{
    ++(*num_of_copies);
}

Shader::~Shader()
{
    --(*num_of_copies);
    if (*num_of_copies > 0) return;

    if (shaderProgram != 0) 
        glDeleteProgram(shaderProgram);

    delete num_of_copies;

}

void Shader::bind() const
{
    glUseProgram(shaderProgram);
}

void Shader::setUniform(const char* name, Mat4f matrix) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
    // in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the values of the matrix to the GPU:
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, (float*) matrix.data);

}

void Shader::setUniform(const char* name, Vec4f vector, int num) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
// in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the values of the vector to the GPU:
    if (loc != -1) {
	    switch (num)
	    {
	    case 2:
            glUniform2f(loc, vector.x, vector.y);
            break;
	    case 3:
            glUniform3f(loc, vector.x, vector.y, vector.z);
            break;
	    case 4:
            glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
            break;
	    default:
            throw std::invalid_argument("'Shader.setUniform<vector>' should only be called with num 2-4.");
	    }
    }

}

void Shader::setUniform(const char* name, float value) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
    // in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the float value to the GPU:
    if (loc != -1)
    {
        glUniform1f(loc, value);
    }

}

void Shader::setUniform(const char* name, int value) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
// in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the integer value to the GPU:
    if (loc != -1)
        glUniform1i(loc, value);

}
