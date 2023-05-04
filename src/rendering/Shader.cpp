
#include "Shader.h"

// Loading files in C++:
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

// Include OpenGL3.3 Core functions:
#include <glad/glad.h>


Shader::Shader(char* vertexShaderName, char* fragmentShaderName, char* sourceDir)
	: numOfCopies(new int(1))
{
    const std::string sSourceDir = std::string(sourceDir);
	const std::string vertexShaderPath = sSourceDir + vertexShaderName;
	const std::string fragmentShaderPath = sSourceDir + fragmentShaderName;

    // Load vertex shader source as string:
    std::ifstream ifs(vertexShaderPath);
    std::string vertexShaderSourceString(std::istreambuf_iterator<char>{ifs}, {});
    const char* vertexShaderSource = vertexShaderSourceString.c_str();
    ifs.close();

    // Load fragment shader source as string:
    ifs = std::ifstream(fragmentShaderPath);
    std::string fragmentShaderSourceString(std::istreambuf_iterator<char>{ifs}, {});
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
    ifs.close();

    // Create temporary pointers to the compiled vertex and fragment shader:
    unsigned int vertexShader;
    unsigned int fragmentShader;

    // Upload VERTEX SHADER source code to GPU and compile it:
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check if compilation was successful, otherwise print error:
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader Compilation failed:\n" << "File: " << vertexShaderPath << infoLog << std::endl;
    }

    // Upload FRAGMENT SHADER source code to GPU and compile it:
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check if compilation was successful, otherwise print error to console:
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment Shader Compilation failed:\n" << "File: " << fragmentShaderPath << infoLog << std::endl;
    }

    // Finally create the shader program which contains both vertex and fragment shader:
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if linking of shaders was successful, otherwise print error to console:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << " (" << vertexShaderPath << ", " << fragmentShaderPath << ")" << std::endl;
    }

    // After shaders were linked to a shader program, we don't need the
    // compiled shaders anymore to run the shader program, so we can delete
    // it on the GPU:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (success)
        initialized = true;
}

Shader::Shader(const Shader& shader)
	: shaderProgram(shader.shaderProgram), initialized(shader.initialized), numOfCopies(shader.numOfCopies)
{
    ++(*numOfCopies);
}

Shader::~Shader()
{
    --(*numOfCopies);
    if (*numOfCopies > 0) return;

    if (shaderProgram != 0) 
        glDeleteProgram(shaderProgram);

    delete numOfCopies;

}

void Shader::bind() const
{
    glUseProgram(shaderProgram);
}

void Shader::setUniform(char* name, Mat4f matrix) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
    // in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the values of the matrix to the GPU:
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, (float*) matrix.data);

}

void Shader::setUniform(char* name, Vec4f vector, int num) const
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

void Shader::setUniform(char* name, float value) const
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

void Shader::setUniform(char* name, int value) const
{
    if (!initialized) return;

    // Gets the location ID where the uniform variable called <name> is stored
// in GPU memory:
    int loc = glGetUniformLocation(shaderProgram, name);

    // If the uniform variable exists, upload the integer value to the GPU:
    if (loc != -1)
        glUniform1i(loc, value);

}
