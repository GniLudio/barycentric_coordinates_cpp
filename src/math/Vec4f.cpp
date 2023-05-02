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
	checkIsVector("toPoint");
	return Vec4f() + *this;
}

Vec4f Vec4f::toVector() const
{
	checkIsPoint("toVector");
	return *this - Vec4f();
}

float Vec4f::length() const
{
	checkIsVector("length");
	return std::sqrt(x * x + y * y + z * z);
}

float Vec4f::squaredLength() const
{
	checkIsVector("squaredLength");
	return x * x + y * y + z * z;
}

float Vec4f::distanceTo(Vec4f p) const
{
	checkIsPoint("distanceTo");
	p.checkIsPoint("distanceTo");
	return (*this - p).length();
}

float Vec4f::dot(Vec4f v) const
{
	checkIsVector("dot");
	v.checkIsVector("dot");
	return x * v.x + y * v.y + z * v.z;
}

Vec4f Vec4f::cross(Vec4f v) const
{
	checkIsVector("cross");
	v.checkIsVector("cross");
	return {
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		0
	};
}

Vec4f Vec4f::normalized() const
{
	checkIsVector("normalized");
	return *this / length();
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
		std::string message = std::string() + "'Vec4f.operator+' shouldn't be used on two points.";
		std::cerr << message << std::endl;
	}
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Vec4f Vec4f::operator-(Vec4f v) const
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Vec4f Vec4f::operator*(float s) const
{
	return { x * s, y * s, z * s, w };
}

Vec4f Vec4f::operator/(float s) const
{
	return { x / s, y / s, z / s, w };
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

std::ostream& operator<<(std::ostream& os, Vec4f vector)
{
	char c = vector.isPoint() ? 'P' : vector.isVector() ? 'V' : '?';
	os << c << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	return os;
}

void Vec4f::checkIsPoint(char* method) const
{
	if (!isPoint())
	{
		std::string message = std::string() + "'Vec4f." + method + "' should only be used on *points*.";
		std::cerr << message << std::endl;
	}
}

void Vec4f::checkIsVector(char* method) const
{
	if (!isVector())
	{
		std::string message = std::string() + "'Vec4f." + method + "' should only be used on *vectors*.";
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
