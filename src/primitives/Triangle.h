#pragma once

#include <iomanip>
#include "Vertex.h"

#include "primitives/Barycentric.h"
#include <iostream>

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

	Vec4f closest(Vec4f point)
	{
		Vec4f a = vertices[0].position, b = vertices[1].position, c = vertices[2].position;
		// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/closest_point_to_triangle.html
		Barycentric barycentric = Barycentric(a, b, c, point);
		if (barycentric[0] >= 0 && barycentric[1] >= 0 && barycentric[2] >= 0 &&
			barycentric[0] <= 1 && barycentric[1] <= 1 && barycentric[2] <= 1)
		{
			// already inside
			return point;
		}
		// the differnt sides
		Vec4f ab = b - a;
		Vec4f bc = c - b;
		Vec4f ca = a - c;

		// closest point to each side
		Vec4f c1 = ab.closest(a, point);
		Vec4f c2 = bc.closest(b, point);
		Vec4f c3 = ca.closest(c, point);

		// distance to each side
		float l1 = (point - c1).squaredLength();
		float l2 = (point - c2).squaredLength();
		float l3 = (point - c3).squaredLength();

		// closest distance
		float min = std::min({l1, l2, l3});

		// returns closest point
		if (l1 <= l2 && l1 <= l3) return c1;
		if (l2 <= l3) return c2;
		return c3;
	}

	Vec4f calculatePoint(Barycentric barycentric)
	{
		return vertices[0].position * barycentric[0]
			+ (vertices[1].position * barycentric[1]).toVector()
			+ (vertices[2].position * barycentric[2]).toVector();
	}
};