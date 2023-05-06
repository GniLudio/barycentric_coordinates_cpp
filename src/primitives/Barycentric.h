#pragma once

#include "math/Mat4f.h"
#include "math/Vec4f.h"

struct Barycentric
{
	float alpha;
	float beta;
	float gamma;

	Barycentric(float alpha = 1/3.f, float beta=1/3.f, float gamma = 1/3.f)
		: alpha(alpha), beta(beta), gamma(gamma)
	{
	}

	Barycentric(Vec4f a, Vec4f b, Vec4f c, Vec4f p)
		: alpha(-1), beta(-1), gamma(-1)
	{
		Vec4f abc[3] = {a,b,c};
		float f = calculateArea(abc);
		Vec4f triangles[3][3] = {
			{p, b, c},
			{p, c, a},
			{p, a, b}
		};
		for (int i=0; i<3; i++)
		{
			(*this)[i] = calculateArea(triangles[i]) / f;
		}
	}

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

	friend std::ostream& operator<<(std::ostream& os, Barycentric barycentric)
	{
		os << "B(" << barycentric.alpha << ", " << barycentric.beta << ", " << barycentric.gamma << ")";
		return os;
	}

private:
	static float calculateArea(Vec4f points[3])
	{
		Vec4f A = points[0], B = points[1], C = points[2];
		return 0.5f * Mat4f(
			{A.x, B.x, C.x},
			{A.y, B.y, C.y},
			{1,1,1}
		).transpose().determinante(3);
	}
};