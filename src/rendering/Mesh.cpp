#include "Mesh.h"

// We use the tiny_obj_loader library to load data of .obj-files into this mesh:
#define TINYOBJLOADER_IMPLEMENTATION

// We want to use triangulation when loading non-triangulated polygons:
#define TINYOBJLOADER_USE_MAPBOX_EARCUT

// Include tiny_obj_loader:
#include <iostream>

#include "tiny_obj_loader.h"

Mesh::Mesh()
	: Shader("simple.vert", "simple.frag"), vertices_num(0)
{
	// creates the vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// creates the vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// gets the attribute handles
	const GLuint position_attr = glGetAttribLocation(shaderProgram, "position");
	const GLuint color_attr = glGetAttribLocation(shaderProgram, "color");

	// Sets the layout
	// Layout (per Triangle): Position A, Color A, Position B, Color B, Position C, Color C
	glVertexAttribPointer(position_attr, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(position_attr);
	glVertexAttribPointer(color_attr, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(color_attr);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<Triangle>& triangles) : Mesh()
{
	uploadData(triangles);
}

Mesh::Mesh(const char* file_name, const char* source_dir) : Mesh()
{
	uploadData(file_name, source_dir);
}

Mesh::~Mesh()
{
	if ((*num_of_copies)-1 > 0) return;

	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
}

void Mesh::render(Mat4f model_matrix) const
{
	bind();
	setUniform("model_matrix", model_matrix);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices_num);
}

void Mesh::uploadData(const std::vector<Triangle>& triangles)
{
	// binds the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// uploads the triangles
	vertices_num = static_cast<unsigned int>(3 * triangles.size());
	glBufferData(GL_ARRAY_BUFFER, vertices_num * sizeof(Vertex), &triangles.front(), GL_STATIC_DRAW);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::uploadData(const char* file_name, const char* source_dir)
{
	std::string filePath = std::string() + source_dir + file_name;
	std::cout << "File Path " << filePath << std::endl;

	std::vector<Triangle> triangles;

	// Define buffers to load the data:
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	// Try to load the obj file into
	if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str()))
	{
		std::cerr << "Obj-file " << filePath << " could not be loaded. Check if file is available." << std::endl;
		return;
	}

	if (!warn.empty())
	{
		std::cout << "Warning while loaded obj-file " << filePath << ":" << std::endl;
		std::cout << warn << std::endl;
		return;
	}
	if (!err.empty())
	{
		std::cout << "Error while loaded obj-file " << filePath << ":" << std::endl;
		std::cerr << err << std::endl;
		return;
	}

	// Loop over shapes of the obj:
	for (auto& shape : shapes)
	{
		// Loop over faces of that shape:
		size_t index_offset = 0;
		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
		{
			int fv = shape.mesh.num_face_vertices[f];

			// Create a triangle for our mesh:
			Triangle triangle;

			// Loop over vertices in the face.
			for (int v = 0; v < fv; v++)
			{
				// access to vertex
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

				// Copy vertex position into triangle:
				std::memcpy(&triangle[v].position, &attrib.vertices[3 * static_cast<size_t>(idx.vertex_index) + 0],
					sizeof(float) * 3);

				// Copy vertex texcoord into triangle if available:
				if (idx.texcoord_index >= 0)
					std::memcpy(&triangle[v].uv, &attrib.texcoords[2 * static_cast<size_t>(idx.texcoord_index) + 0],
						sizeof(float) * 2);

				// Copy vertex color into triangle:
				std::memcpy(&triangle[v].color, &attrib.colors[3 * static_cast<size_t>(idx.vertex_index) + 0],
					sizeof(float) * 3);
			}

			// Generate normals:
			{
				Vec4f v1 = triangle[1].position - triangle[0].position;
				Vec4f v2 = triangle[2].position - triangle[0].position;
				Vec4f normal = v1.cross(v2).normalized();
				for (int v = 0; v < fv; ++v)
				{
					triangle[v].normal = normal;
				}
			}

			index_offset += fv;

			triangles.push_back(triangle);
		}
	}

	// uploads the triangles
	uploadData(triangles);
}