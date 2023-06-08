#pragma once
#include "math/Mat4f.h"

class Shader
{
public:
	/** Stores the ID of the shader program on the GPU */
	unsigned int shaderProgram;

public:
	/**
	 * Loads the source code of the given file paths, compiles it on the
	 * GPU and stores the reference (=id, =name) to the program in the
	 * attribute 'shaderProgram'.
	 *
	 * NOTE:
	 * OpenGL shaders are usually not compiled when the C++ program
	 * is compiled, but only when the program is started. I.e. we have
	 * to read in from the source files at this point and then pass it
	 * to OpenGL to be compiled on the graphics card.
	 *
	 * In recent OpenGL versions, it is also possible to compile shaders
	 * before hand (so they don't have to be compiled every time you
	 * start a game, but that's another topic ;-)).
	 */
	Shader(char* vertexShaderName, char* fragmentShaderName, char* sourceDir = CMAKE_SOURCE_DIR "/shader/");

	/**
	 * Explicit copy constructor for reference counting (for correct
	 * shaderProgram deletion).
	 */
	Shader(const Shader& shader);

	/**
	 * Deletes the shader and ensures that the memory on the GPU
	 * is cleaned up.
	 */
	~Shader(void);

	/**
	 * Binds the shader so that it will be used in future draw calls.
	 */
	void bind(void) const;

	/** Sets a uniform *matrix* variable. */
	void setUniform(char* name, Mat4f matrix) const;

	/** Sets a uniform *vector* variable. */
	void setUniform(char* name, Vec4f vector, int num = 4) const;

	/** Sets a uniform *float* variable. */
	void setUniform(char* name, float value) const;

	/** Sets a uniform *int* variable. */
	void setUniform(char* name, int value) const;

protected:
	/** Is set to true in the constructor if initialization worked: */
	bool initialized = false;

	// Copy counter (This is needed for correct creation and deletion
	// of shaderProgram on GPU, since C++ copies objects on reassignment,
	// see copy constructor. In general, I would recommend holding Mesh,
	// Shader, SpinningTop and World objects by a shared_ptr instead of
	// doing this, because that ensures that exactly one explicitly created
	// mesh object exists, but we don't want to introduce 'Smart Pointers'
	// in Computergrafik 1 - just as a hint if you want to create your
	// own engine):
	int* numOfCopies;
};
