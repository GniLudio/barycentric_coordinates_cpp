#pragma once

// Include std::vector
#include <vector>

// Include OpenGL3.3 Core functions:
#include <glad/glad.h>

// Include shader class
#include "Shader.h"

// Include Triangle primitive
#include "primitives/Triangle.h"


class Mesh
{
public:
	/** Creates an empty mesh. */
	Mesh();

	/** Creates a mesh out of the triangles. */
	Mesh(const std::vector<Triangle>& triangles);

	/** Creates a mesh with the geometry data of an .obj file. */
	Mesh(char* fileName, char* sourceDir = CMAKE_SOURCE_DIR "/models/");

	/** Explicit copy constructor for reference counting. */
	Mesh(const Mesh& mesh);

	/** Destructor. */
	~Mesh();

	/** Renders the mesh. */
	void render(Mat4f modelMatrix) const;

	/** Uploads the triangle data. */
	void uploadData(const std::vector<Triangle>& triangles);

	/** Uploads the geometry data of an obj. file. */
	void uploadData(char* fileName, char* sourceDir = CMAKE_SOURCE_DIR "/models/");
private:
	const Shader shader;

	// The VAO and VBO
	GLuint vao, vbo;

	// Number of vertices
	unsigned int verticesNum;

	// Copy counter (This is needed for correct creation and deletion
	// of VAO/VBOs, since C++ copies objects on reassignment, see copy
	// constructor. In general, I would recommend holding Mesh, Shader,
	// SpinningTop and World objects by a shared_ptr instead of doing
	// this, because that ensures that exactly one explicitly created
	// mesh object exists, but we don't want to introduce 'Smart Pointers'
	// in Computergrafik 1 - just as a hint if you want to create your
	// own engine):
	int* numOfCopies;
};
