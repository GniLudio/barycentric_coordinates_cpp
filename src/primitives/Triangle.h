#pragma once

#include <iomanip>
#include "Vertex.h"

#include "primitives/Barycentric.h"

/**
 * \brief A triangle.
 */
struct Triangle
{
	/**
	 * \brief The vertices.
	 */
	Vertex vertices[3];

	/**
	 * \brief The constructor.
	 * \param a The first vertex.
	 * \param b The second vertex.
	 * \param c The third vertex.
	 */
	Triangle(Vertex a = {}, Vertex b = {}, Vertex c = {})
		: vertices{a,b,c}
	{
	}

	/**
	 * \brief The constructor.
	 * \param vertices The vertices.
	 */
	Triangle(Vertex vertices[3]) : vertices{vertices[0], vertices[1], vertices[2]}
	{
	}

	/**
	 * \brief Returns a specific vertex.
	 * \param i The index.
	 * \return The vertex.
	 */
	Vertex& operator[](int i) {
		if (i < 0 || i > 2) 
			throw std::invalid_argument("'Triangle.operator[]' should only be called with indices 0-2.");
		return vertices[i];
	}

	/**
	 * \brief Returns a specific vertex.
	 * \param i The index.
	 * \return The vertex.
	 */
	Vertex operator[](int i) const {
		if (i < 0 || i > 2)
			throw std::invalid_argument("'Triangle.operator[]' should only be called with indices 0-2.");
		return vertices[i];
	}

	/**
	 * \brief Returns the closest point in the triangle to a another point.
	 * \param point The other point.
	 * \return The closest point in the triangle.
	 */
	Vec4f closest_in_triangle(Vec4f point) const
	{
		// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/closest_point_to_triangle.html

		const Vec4f a = vertices[0].position, b = vertices[1].position, c = vertices[2].position;

		// the point is already inside the triangle
		Barycentric barycentric = Barycentric(a, b, c, point);
		if (barycentric[0] >= 0 && barycentric[1] >= 0 && barycentric[2] >= 0 &&
			barycentric[0] <= 1 && barycentric[1] <= 1 && barycentric[2] <= 1)
		{
			return point;
		}
		// the different sides
		const Vec4f ab = b - a, bc = c - b, ca = a - c;

		// closest point to each side
		const Vec4f c1 = ab.closest(a, point), c2 = bc.closest(b, point), c3 = ca.closest(c, point);

		// distance to each side
		float l1 = (point - c1).squaredLength();
		float l2 = (point - c2).squaredLength();
		float l3 = (point - c3).squaredLength();

		// smallest distance
		float min = std::min({l1, l2, l3});

		// returns closest point
		if (l1 <= l2 && l1 <= l3) return c1;
		if (l2 <= l3) return c2;
		return c3;
	}

	/**
	 * \brief Calculates the point of this triangle and barycentric coordinates.
	 * \param barycentric The barycentric coordinates.
	 * \return The point.
	 */
	Vec4f calculate_point(Barycentric barycentric) const
	{
		return vertices[0].position * barycentric[0]
			+ (vertices[1].position * barycentric[1]).toVector()
			+ (vertices[2].position * barycentric[2]).toVector();
	}
};