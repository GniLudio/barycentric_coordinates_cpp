#pragma once

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
		// TODO: Calculate the barycentric coordinates of point p in the triangle 
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
};