#pragma once

// Include std::vector
#include <vector>

// Include OpenGL3.3 Core functions:
#include <glad/glad.h>

// Include shader class
#include "Shader.h"

// Include Triangle primitive
#include "primitives/Triangle.h"

/**
 * \brief A mesh.
 */
class Mesh : protected Shader
{
public:
	/**
	 * \brief The constructor for a empty mesh.
	 */
	explicit Mesh();

	/**
	 * \brief The constructor.
	 * \param triangles The triangles.
	 */
	explicit Mesh(const std::vector<Triangle>& triangles);

	/**
	 * \brief The constructor.
	 * \param file_name The .obj file name.
	 * \param source_dir The directory of the .obj file.
	 */
	explicit Mesh(const char* file_name, const char* source_dir = CMAKE_SOURCE_DIR "/models/");

	/**
	 * \brief The destructor.
	 */
	~Mesh();

	/**
	 * \brief Renders the mesh.
	 * \param model_matrix The model matrix.
	 */
	void render(Mat4f model_matrix) const;

	/**
	 * \brief Uploads the data.
	 * \param triangles The triangles.
	 */
	void uploadData(const std::vector<Triangle>& triangles);

	/**
	 * \brief Uploads the data.
	 * \param file_name The .obj file name.
	 * \param source_dir The directory of the .obj file.
	 */
	void uploadData(const char* file_name, const char* source_dir = CMAKE_SOURCE_DIR "/models/");
protected:
	/**
	 * \brief The vertex array object.
	 */
	GLuint vao;

	/**
	 * \brief The vertex buffer object.
	 */
	GLuint vbo;

	/**
	 * \brief The number of vertices
	 */
	unsigned int vertices_num;
};
