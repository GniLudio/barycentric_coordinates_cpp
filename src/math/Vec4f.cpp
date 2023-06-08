#include "Vec4f.h"

#include <iostream>

Vec4f::Vec4f(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Vec4f::Vec4f(float data[4])
	: Vec4f(data[0], data[1], data[2], data[3])
{
}

Vec4f Vec4f::toPoint() const
{
	checkIsVector("toPoint (this)");
	return Vec4f() + *this;
}

Vec4f Vec4f::toVector() const
{
	checkIsPoint("toVector (this)");
	return *this - Vec4f();
}

float Vec4f::length(int dimensions) const
{
	if (dimensions < 0 || dimensions > 4)
		throw std::invalid_argument("Vec4f.length should be called with dimensions between 0-4");
	checkIsVector("length (this)");
	float l = 0;
	for (int i=0; i<dimensions; i++)
	{
		l += (*this)[i] * (*this)[i];
	}
	l = std::sqrt(l);
	return l;
}

float Vec4f::squaredLength(int dimensions) const
{
	if (dimensions < 0 || dimensions > 4)
		throw std::invalid_argument("Vec4f.squaredLength should be called with dimensions between 0-4");
	checkIsVector("squaredLength (this)");
	float l = 0;
	for (int i = 0; i < dimensions; i++)
	{
		l += (*this)[i] * (*this)[i];
	}
	return l;
}

float Vec4f::distanceTo(Vec4f p, int dimensions) const
{
	checkIsPoint("distanceTo (this)");
	p.checkIsPoint("distanceTo (p)");
	return (*this - p).length(dimensions);
}

float Vec4f::dot(Vec4f vector) const
{
	checkIsVector("dot (this)");
	vector.checkIsVector("dot (vector)");
	return x * vector.x + y * vector.y + z * vector.z;
}

Vec4f Vec4f::cross(Vec4f vector) const
{
	checkIsVector("cross (this)");
	vector.checkIsVector("cross  (vector)");
	return {
		y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x,
		0
	};
}

Vec4f Vec4f::normalized(int dimensions) const
{
	checkIsVector("normalized (this)");
	return *this / length(dimensions);
}

Vec4f Vec4f::closest(Vec4f start, Vec4f point) const
{
	// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter1/closest_point_on_line.html

	checkIsVector("closest (this)");
	start.checkIsPoint("closest (start)");
	point.checkIsPoint("closest (point)");

	float t = (point-start).dot(*this) / this->dot(*this);
	t = std::max(0.f, std::min(t, 1.f));

	return start + *this * t;
}

bool Vec4f::operator==(Vec4f v) const
{
	return
		std::abs(x - v.x) <= COMPARE_DELTA &&
		std::abs(y - v.y) <= COMPARE_DELTA &&
		std::abs(z - v.z) <= COMPARE_DELTA &&
		std::abs(w - v.w) <= COMPARE_DELTA;

}

bool Vec4f::operator!=(Vec4f v) const
{
	return
		std::abs(x - v.x) > COMPARE_DELTA ||
		std::abs(y - v.y) > COMPARE_DELTA ||
		std::abs(z - v.z) > COMPARE_DELTA ||
		std::abs(w - v.w) > COMPARE_DELTA;

}

Vec4f Vec4f::operator-() const
{
	return { -x, -y, -z, -w };
}

Vec4f Vec4f::operator+(Vec4f v) const
{
	if (isPoint() && v.isPoint())
	{
		const std::string message = std::string() + "'Vec4f.operator+' shouldn't be used on two points.";
		std::cerr << message << std::endl;
	}
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Vec4f Vec4f::operator-(Vec4f v) const
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Vec4f Vec4f::operator*(float scalar) const
{
	return { x * scalar, y * scalar, z * scalar, w };
}

Vec4f Vec4f::operator/(float scalar) const
{
	return { x / scalar, y / scalar, z / scalar, w };
}

float& Vec4f::operator[](int i)
{
	switch (i)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: 
			throw std::invalid_argument("'Vec4f.operator[] should only be called with the indices 0-3.");
	}
}

float Vec4f::operator[](int i) const
{
	switch (i)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default:
			throw std::invalid_argument("'Vec4f.operator[] should only be called with the indices 0-3.");
	}
}

std::ostream& operator<<(std::ostream& os, Vec4f v)
{
	const char c = v.isPoint() ? 'P' : v.isVector() ? 'V' : '?';
	os << c << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}

void Vec4f::checkIsPoint(const char* method) const
{
	if (!isPoint())
	{
		std::string message = std::string() + "'Vec4f." + method + "' should only be used with *points*.";
		std::cerr << message << std::endl;
	}
}

void Vec4f::checkIsVector(const char* method) const
{
	if (!isVector())
	{
		std::string message = std::string() + "'Vec4f." + method + "' should only be used with *vectors*.";
		std::cerr << message << std::endl;
	}
}

bool Vec4f::isPoint() const
{
	return std::abs(1 - w) <= COMPARE_DELTA;
}

bool Vec4f::isVector() const
{
	return std::abs(w) <= COMPARE_DELTA;
}
