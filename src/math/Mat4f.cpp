#include "Mat4f.h"

#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>

Mat4f::Mat4f(Vec4f v1, Vec4f v2, Vec4f v3, Vec4f v4) : data{v1,v2,v3,v4}
{
}

Mat4f::Mat4f(Vec4f data[4]) : data{data[0], data[1], data[2], data[3]}
{
}

Mat4f::Mat4f(float data[16]) : data{ Vec4f(&data[0]), Vec4f( & data[4]), Vec4f( & data[8]), Vec4f(&data[12])}
{
}

Mat4f Mat4f::operator*(Mat4f matrix) const
{
	Mat4f result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[j][i] = 0
				+ (*this)[0][i] * matrix[j][0]
				+ (*this)[1][i] * matrix[j][1]
				+ (*this)[2][i] * matrix[j][2]
				+ (*this)[3][i] * matrix[j][3];
		}
	}
	return result;
}

Vec4f Mat4f::operator*(Vec4f vector) const
{
	Vec4f result;
	for (int i = 0; i < 4; i++)
	{
		result[i] = 0
			+ (*this)[0][i] * vector[0]
			+ (*this)[1][i] * vector[1]
			+ (*this)[2][i] * vector[2]
			+ (*this)[3][i] * vector[3];
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

float Mat4f::determinante(int size) const
{
	switch (size)
	{
	case 2:
		return 0
			+ (*this)[0][0] * (*this)[1][1]
			- (*this)[0][1] * (*this)[1][0];
	case 3:
		return 0
			+ (*this)[0][0] * (*this)[1][1] * (*this)[2][2]
			- (*this)[0][2] * (*this)[1][1] * (*this)[2][0]
			+ (*this)[1][0] * (*this)[2][1] * (*this)[0][2]
			- (*this)[1][2] * (*this)[2][1] * (*this)[0][0]
			+ (*this)[2][0] * (*this)[0][1] * (*this)[1][2]
			- (*this)[2][2] * (*this)[0][1] * (*this)[1][0];
	default:
		throw std::invalid_argument("'Mat4f.determinante' should only be called with size 2 or 3.");
	}
}

Mat4f Mat4f::inverse() const
{
	float det = determinante();
	if (det == 0)
		throw std::invalid_argument("The determinant has to be unequal 0.");
	float det_inv = 1 / det;
	Mat4f result;
	result[0][0] = ((*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1]) * det_inv;
	result[1][0] = ((*this)[2][0] * (*this)[1][2] - (*this)[1][0] * (*this)[2][2]) * det_inv;
	result[2][0] = ((*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1]) * det_inv;
	result[0][1] = ((*this)[2][1] * (*this)[0][2] - (*this)[0][1] * (*this)[2][2]) * det_inv;
	result[1][1] = ((*this)[0][0] * (*this)[2][2] - (*this)[2][0] * (*this)[0][2]) * det_inv;
	result[2][1] = ((*this)[0][1] * (*this)[2][0] - (*this)[0][0] * (*this)[2][1]) * det_inv;
	result[0][2] = ((*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1]) * det_inv;
	result[1][2] = ((*this)[0][2] * (*this)[1][0] - (*this)[0][0] * (*this)[1][2]) * det_inv;
	result[2][2] = ((*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]) * det_inv;
	return result;

}

std::ostream& operator<<(std::ostream& os, Mat4f matrix)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			os << std::left << std::setw(7) << std::setprecision(4) << matrix[x][y] << std::setfill(' ');
		}
		if (y != 3) os << std::endl;
	}
	return os;

}

Mat4f Mat4f::translation(float x, float y, float z)
{
	Mat4f result;
	result[3] = { x,y,z,1 };
	return {};
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
	fov *= (float)M_PI;

	Mat4f result;
	result[0][0] = cosf(fov / 2) / sinf(fov / 2) / aspectRatio;
	result[1][1] = cosf(fov / 2) / sinf(fov / 2);
	result[2][2] = (far + near) / (far - near);
	result[2][3] = 1;
	result[3][2] = (-2 * far * near) / (far - near);
	result[3][3] = 0;
	return result;

}
