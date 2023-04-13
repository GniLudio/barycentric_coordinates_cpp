#pragma once

#include <iomanip>
#include "Vertex.h"

struct Triangle
{
	/** The vertices of the triangle. */
	Vertex vertices[3];

	Triangle(Vertex a = {}, Vertex b = {}, Vertex c = {})
		: vertices{a,b,c}
	{
	}

	Triangle(Vertex vertices[3]) : vertices{vertices[0], vertices[1], vertices[2]}
	{
	}

	Vertex& operator[](int i) {
		if (i < 0 || i > 2) 
			throw std::invalid_argument("'Triangle.operator[]' should only be called with indices 0-2.");
		return vertices[i];
	}

	Vertex operator[](int i) const {
		if (i < 0 || i > 2)
			throw std::invalid_argument("'Triangle.operator[]' should only be called with indices 0-2.");
		return vertices[i];
	}
};