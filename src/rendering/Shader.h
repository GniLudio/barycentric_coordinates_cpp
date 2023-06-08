#pragma once
#include "math/Mat4f.h"

/**
 * \brief A shader.
 */
class Shader
{
public:
	/**
	 * \brief The constructor.
	 * \param vertex_shader The file name of the vertex shader.
	 * \param fragment_shader The file name of the fragment shader.
	 * \param source_dir The directory of the vertex and fragment shaders.
	 */
	explicit Shader(const char* vertex_shader, const char* fragment_shader, const char* source_dir = CMAKE_SOURCE_DIR "/shader/");

	/**
	 * \brief The copy constructor for reference counting.
	 * \param shader The shader.
	 */
	Shader(const Shader& shader);

	/**
	 * \brief The destructor.
	 */
	~Shader(void);

public:
	/**
	 * \brief The id of the shader program.
	 */
	unsigned int shaderProgram;

	/**
	 * \brief Binds the shader.
	 */
	void bind(void) const;

	/**
	 * \brief Sets a uniform matrix.
	 * \param name The variable name.
	 * \param matrix The matrix.
	 */
	void setUniform(const char* name, Mat4f matrix) const;

	/**
	 * \brief Sets a uniform vector.
	 * \param name The variable name.
	 * \param vector The vector.
	 * \param num The number of dimensions.
	 */
	void setUniform(const char* name, Vec4f vector, int num = 4) const;

	/**
	 * \brief Sets a uniform float.
	 * \param name The variable name.
	 * \param value The float.
	 */
	void setUniform(const char* name, float value) const;

	/**
	 * \brief Sets a uniform integer.
	 * \param name The variable name.
	 * \param value The integer.
	 */
	void setUniform(const char* name, int value) const;

protected:
	/**
	 * \brief Whether the initialization worked.
	 */
	bool initialized = false;

	/**
	 * \brief The number of copies.
	 */
	int* num_of_copies;


};
