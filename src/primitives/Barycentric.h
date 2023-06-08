#pragma once

#include "math/Mat4f.h"
#include "math/Vec4f.h"

/**
 * \brief The barycentric coordinates.
 */
struct Barycentric
{
	/**
	 * \brief The alpha component.
	 */
	float alpha;
	/**
	 * \brief The beta component.
	 */
	float beta;
	/**
	 * \brief The gamma component.
	 */
	float gamma;

	/**
	 * \brief The constructor.
	 * \param alpha The alpha component.
	 * \param beta The beta component.
	 * \param gamma The gamma component.
	 */
	explicit Barycentric(float alpha = 1/3.f, float beta=1/3.f, float gamma = 1/3.f)
		: alpha(alpha), beta(beta), gamma(gamma)
	{
	}

	/**
	 * \brief Calculates the barycentric coordinates of a point and a triangle.
	 * \param a The first vertex of the triangle..
	 * \param b The second vertex of the triangle.
	 * \param c The third vertex of the triangle.
	 * \param p The point.
	 */
	explicit Barycentric(Vec4f a, Vec4f b, Vec4f c, Vec4f p)
		: alpha(-1), beta(-1), gamma(-1)
	{
		Vec4f abc[3] = { a, b, c};
		Vec4f pbc[3] = { p, b, c };
		Vec4f pca[3] = { p, c, a };
		Vec4f pab[3] = { p, a, b };

		const float f_all = calculateArea(abc);
		(*this)[0] = calculateArea(pbc) / f_all;
		(*this)[1] = calculateArea(pca) / f_all;
		(*this)[2] = calculateArea(pab) / f_all;
	}

	/**
	 * \brief Returns a specific component.
	 * \param i The index. (0-2)
	 * \return The component.
	 */
	float& operator[](int i) {
		switch (i)
		{
			case 0: return alpha;
			case 1: return beta;
			case 2: return gamma;
			default:
				throw std::invalid_argument("Barycentric.operator[] should only be called with indices 0-2");
		}
	}

	/**
	 * \brief Returns a specific component.
	 * \param i The index. (0-2)
	 * \return The component.
	 */
	float operator[](int i) const {
		switch (i)
		{
			case 0: return alpha;
			case 1: return beta;
			case 2: return gamma;
			default:
				throw std::invalid_argument("Barycentric.operator[] should only be called with indices 0-2");
		}
	}

	/**
	 * \brief Prints the barycentric coordinates.
	 * \param os The output stream.
	 * \param barycentric The barycentric coordinates.
	 * \return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, Barycentric barycentric)
	{
		os << "B(" << barycentric.alpha << ", " << barycentric.beta << ", " << barycentric.gamma << ")";
		return os;
	}

private:
	/**
	 * \brief Calculates the area of a triangle.
	 * \param triangle The triangle
	 * \return The triangle area.
	 */
	static float calculateArea(Vec4f triangle[3])
	{
		const Vec4f A = triangle[0], B = triangle[1], C = triangle[2];
		return 0.5f * Mat4f(
			{A.x, B.x, C.x},
			{A.y, B.y, C.y},
			{1,1,1}
		).transpose().determinante(3);
	}
};