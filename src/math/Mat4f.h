#pragma once
#include "Vec4f.h"

/**
 * A 4x4 Matrix.
 *
 * Note that the matrix is in column-major order. (like OpenGL does)
 */
struct Mat4f
{
public:
	/** The columns of this matrix. */
	Vec4f data[4];

public:

	/** The constructor */
	Mat4f(Vec4f v1 = { 1,0,0,0 }, Vec4f v2 = { 0,1,0,0 }, Vec4f v3 = { 0,0,1,0 }, Vec4f v4 = {0,0,0,1});

	/** The constructor. */
	Mat4f(Vec4f data[4]);

	/** The constructor. */
	Mat4f(float data[16]);

public:
	/** Returns the multiplication with the given matrix. */
	Mat4f operator*(Mat4f matrix) const;

	/** Returns the multiplication with the given vector. */
	Vec4f operator*(Vec4f vector) const;

	/** Returns a column of this matrix. */
	Vec4f& operator[](int i);

	/** Returns a column of this matrix. */
	Vec4f operator[](int i) const;

public:
	/** Returns the determinante of this matrix. */
	float determinante(int size = 3) const;

	/** Returns the inverse of this matrix. */
	Mat4f inverse() const;

public:
	/**
	 * Adds the given Mat4f to an output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, Mat4f matrix);

public:
	/** Returns a transformation matrix which performs a translation. */
	static Mat4f translation(float x, float y, float z);

	/** Returns a transformation matrix which performs a rotation around the x axis. */
	static Mat4f rotationX(float angle);

	/** Returns a transformation matrix which performs a rotation around the y axis. */
	static Mat4f rotationY(float angle);


	/** Returns a transformation matrix which performs a rotation around the y axis. */
	static Mat4f rotationZ(float angle);

	/** Returns a transformation matrix which performs a uniform scaling. */
	static Mat4f scale(float scale);

	/** Returns a transformation matrix which performs a scaling. */
	static Mat4f scale(float xScale, float yScale, float zScale);

	/** Returns a matrix which performs the perpective transformation. */
	static Mat4f perspectiveTransformation(
		float aspectRatio = 1.f,
		float fov = 75.f,
		float near = 0.01f,
		float far = 1000.f
	);
};
