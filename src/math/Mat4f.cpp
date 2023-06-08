#include "Mat4f.h"

#include <iomanip>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

Mat4f::Mat4f(Vec4f v1, Vec4f v2, Vec4f v3, Vec4f v4) : data{v1, v2, v3, v4}
{
}

Mat4f::Mat4f(Vec4f data[4]) : data{data[0], data[1], data[2], data[3]}
{
}

Mat4f::Mat4f(float data[16]) : data{Vec4f(&data[0]), Vec4f(&data[4]), Vec4f(&data[8]), Vec4f(&data[12])}
{
}

Mat4f Mat4f::operator*(Mat4f matrix) const
{
	const Mat4f& m = *this;
	Mat4f result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[j][i] = 0
				+ m[0][i] * matrix[j][0]
				+ m[1][i] * matrix[j][1]
				+ m[2][i] * matrix[j][2]
				+ m[3][i] * matrix[j][3];
		}
	}
	return result;
}

Vec4f Mat4f::operator*(Vec4f vector) const
{
	const Mat4f& m = *this;
	Vec4f result;
	for (int i = 0; i < 4; i++)
	{
		result[i] = 0
			+ m[0][i] * vector[0]
			+ m[1][i] * vector[1]
			+ m[2][i] * vector[2]
			+ m[3][i] * vector[3];
	}
	return result;
}

Mat4f Mat4f::operator*(float scalar) const
{
	const Mat4f& m = *this;
	Mat4f result;
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			result[x][y] = scalar * m[x][y];
		}
	}
	return result;
}

Vec4f& Mat4f::operator[](int i)
{
	if (i < 0 || i > 3)
		throw std::invalid_argument("'Mat4f.operator[]' should only be called with indices 0-3.");
	return data[i];
}

Vec4f Mat4f::operator[](int i) const
{
	if (i < 0 || i > 3)
		throw std::invalid_argument("'Mat4f.operator[]' should only be called with indices 0-3.");
	return data[i];
}

bool Mat4f::operator==(Mat4f matrix) const
{
	const Mat4f& m = *this;
	return
		m[0] == matrix[0] && 
		m[1] == matrix[1] && 
		m[2] == matrix[2] && 
		m[3] == matrix[3];
}

bool Mat4f::operator!=(Mat4f matrix) const
{
	const Mat4f& m = *this;
	return
		m[0] != matrix[0] ||
		m[1] != matrix[1] ||
		m[2] != matrix[2] ||
		m[3] != matrix[3];
}

float Mat4f::determinante(int size) const
{
	const Mat4f& m = *this;
	switch (size)
	{
	case 2:
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	case 3:
		return
			+ m[0][0] * m[1][1] * m[2][2]
			- m[0][2] * m[1][1] * m[2][0]
			+ m[1][0] * m[2][1] * m[0][2]
			- m[1][2] * m[2][1] * m[0][0]
			+ m[2][0] * m[0][1] * m[1][2]
			- m[2][2] * m[0][1] * m[1][0];
	case 4:
		// see https://semath.info/src/inverse-cofactor-ex4.html
		return
			+ m[0][0] * (
				+ m[1][1] * m[2][2] * m[3][3] + m[2][1] * m[3][2] * m[1][3] + m[3][1] * m[1][2] * m[2][3]
				- m[3][1] * m[2][2] * m[1][3] - m[2][1] * m[1][2] * m[3][3] - m[1][1] * m[3][2] * m[2][3]
			)
			- m[0][1] * (
				+ m[1][0] * m[2][2] * m[3][3] + m[2][0] * m[3][2] * m[1][3] + m[3][0] * m[1][2] * m[2][3]
				- m[3][0] * m[2][2] * m[1][3] - m[2][0] * m[1][2] * m[3][3] - m[1][0] * m[3][2] * m[2][3]
			)
			+ m[0][2] * (
				+ m[1][0] * m[2][1] * m[3][3] + m[2][0] * m[3][1] * m[1][3] + m[3][0] * m[1][1] * m[2][3]
				- m[3][0] * m[2][1] * m[1][3] - m[2][0] * m[1][1] * m[3][3] - m[1][0] * m[3][1] * m[2][3]
			)
			- m[0][3] * (
				+ m[1][0] * m[2][1] * m[3][2] + m[2][0] * m[3][1] * m[1][2] + m[3][0] * m[1][1] * m[2][2]
				- m[3][0] * m[2][1] * m[1][2] - m[2][0] * m[1][1] * m[3][2] - m[1][0] * m[3][1] * m[2][2]
			);
	default:
		throw std::invalid_argument("'Mat4f.determinante' should only be called with size 2 or 3.");
	}
}

Mat4f Mat4f::adjugate() const
{
	const Mat4f& m = *this;
	Mat4f result;
	// see https://semath.info/src/inverse-cofactor-ex4.html
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			// 3x3 matrix without the ij row and column
			Mat4f jiMatrix = Mat4f();
			for (int x=0, dx=0; x<4; x++)
			{
				if (x == j) continue;
				for (int y=0, dy=0; y<4; y++)
				{
					if (y == i) continue;
					jiMatrix[dx][dy] = m[x][y];
					dy++;
				}
				dx++;
			}
			result[i][j] = ((j+i) % 2 == 0 ? 1 : -1) * jiMatrix.determinante();
		}
	}
	return result;
}

Mat4f Mat4f::inverse() const
{
	float det = this->determinante(4);
	Mat4f adj = this->adjugate();
	return adj * (1.f / det);
}

Mat4f Mat4f::transpose() const
{
	const Mat4f& m = *this;
	Mat4f result;
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			result[y][x] = m[x][y];
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, Mat4f matrix)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			float number = matrix[x][y];
			bool pretty = false;
			if (std::abs(number) < COMPARE_DELTA)
			{
				pretty = true;
				number = 0;
			}
			else if (std::abs(1 - number) < COMPARE_DELTA)
			{
				pretty = true;
				number = 1;
			}

			if (pretty)
				os << std::left << "~" << std::setw(6) << std::setprecision(3) << number << std::setfill(' ');
			else 
				os << std::left << std::setw(7) << std::setprecision(3) << number << std::setfill(' ');

		}
		os << std::endl;
	}
	return os;
}

Mat4f Mat4f::translation(float x, float y, float z)
{
	Mat4f result;
	result[3] = {x, y, z, 1};
	return result;
}

Mat4f Mat4f::rotationX(float angle)
{
	Mat4f result;
	result[1][1] = std::cosf(angle);
	result[1][2] = std::sinf(angle);
	result[2][1] = -std::sinf(angle);
	result[2][2] = std::cosf(angle);
	return result;
}

Mat4f Mat4f::rotationY(float angle)
{
	Mat4f result;
	result[0][0] = std::cosf(angle);
	result[2][0] = std::sinf(angle);
	result[0][2] = -std::sinf(angle);
	result[2][2] = std::cosf(angle);
	return result;
}

Mat4f Mat4f::rotationZ(float angle)
{
	Mat4f result;
	result[0][0] = std::cosf(angle);
	result[1][0] = -std::sinf(angle);
	result[0][1] = std::sinf(angle);
	result[1][1] = std::cosf(angle);
	return result;
}

Mat4f Mat4f::rotation(float angleX, float angleY, float angleZ)
{
	return rotationX(angleX) * rotationY(angleY) * rotationZ(angleZ);
}

Mat4f Mat4f::scale(float scale)
{
	return Mat4f::scale(scale, scale, scale);
}

Mat4f Mat4f::scale(float xScale, float yScale, float zScale)
{
	Mat4f result;
	result[0][0] = xScale;
	result[1][1] = yScale;
	result[2][2] = zScale;
	return result;
}

Mat4f Mat4f::perspectiveTransformation(float aspectRatio, float fov, float near, float far)
{
	fov *= static_cast<float>(M_PI);

	Mat4f result;
	result[0][0] = cosf(fov / 2) / sinf(fov / 2) / aspectRatio;
	result[1][1] = cosf(fov / 2) / sinf(fov / 2);
	result[2][2] = (far + near) / (far - near);
	result[2][3] = 1;
	result[3][2] = (-2 * far * near) / (far - near);
	result[3][3] = 0;
	return result;
}
