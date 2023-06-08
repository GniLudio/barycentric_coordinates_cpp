#pragma once
#include "Vec4f.h"

/**
 * \brief A 4x4 matrix in column-major order.
 */
struct Mat4f
{
public:
	/**
	 * \brief The columns of this matrix.
	 */
	Vec4f data[4];

public:
	/**
	 * \brief The constructor
	 * \param v1 The first column.
	 * \param v2 The second column.
	 * \param v3 The third column.
	 * \param v4 The fourth column.
	 */
	explicit Mat4f(Vec4f v1 = { 1,0,0,0 }, Vec4f v2 = { 0,1,0,0 }, Vec4f v3 = { 0,0,1,0 }, Vec4f v4 = {0,0,0,1});

	/**
	 * \brief The constructor.
	 * \param data The data.
	 */
	explicit Mat4f(Vec4f data[4]);

	/**
	 * \brief The constructor.
	 * \param data The data.
	 */
	explicit Mat4f(float data[16]);

public:
	/**
	 * \brief Returns the multiplication with the given matrix.
	 * \param matrix The other matrix.
	 * \return The multiplication.
	 */
	Mat4f operator*(Mat4f matrix) const;

	/**
	 * \brief Returns the multiplication with the given vector.
	 * \param vector The vector.
	 * \return The transformed vector.
	 */
	Vec4f operator*(Vec4f vector) const;

	/**
	 * \brief Multiplies this matrix with the given scalar.
	 * \param scalar The scalar.
	 * \return The multiplied matrix.
	 */
	Mat4f operator*(float scalar) const;

	/**
	 * \brief Returns a column of this matrix.
	 * \param i The index.
	 * \return The column.
	 */
	Vec4f& operator[](int i);

	/**
	 * \brief Returns a column of this matrix.
	 * \param i The index.
	 * \return The column.
	 */
	Vec4f operator[](int i) const;

	/**
	 * \brief Checks that the difference of each component is smaller or equal to 'COMPARE_DELTA'.
	 * \param matrix The other matrix.
	 * \return Whether the matrices are equal.
	 */
	bool operator==(Mat4f matrix) const;

	/**
	 * \brief Checks if at least one component has a higher difference than 'COMPARE_DELTA'.
	 * \param matrix The other matrix.
	 * \return Whether the matrices are not equal.
	 */
	bool operator!=(Mat4f matrix) const;
public:
	/**
	 * \brief Returns the determinante of this matrix.
	 * \param size The size. (2, 3 oder 4)
	 * \return The determinante.
	 */
	float determinante(int size = 3) const;

	/**
	 * \brief Returns the adjugate of this matrix.
	 * \return The adjugate.
	 */
	Mat4f adjugate() const;

	/**
	 * \brief Returns the inverse of this matrix.
	 * \return The inverse.
	 */
	Mat4f inverse() const;

	/**
	 * \brief Returns the tranposed matrix.
	 * \return The transposed matrix.
	 */
	Mat4f transpose() const;
public:
	/**
	 * \brief Adds the given Mat4f to an output stream.
	 * \param os The output stream.
	 * \param matrix The matrix.
	 * \return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, Mat4f matrix);

public:
	/* */
	/**
	 * \brief Returns a matrix which performs a translation.
	 * \param x The translation on the x-axis.
	 * \param y The translation on the y-axis.
	 * \param z The translation on the z-axis.
	 * \return The translation matrix.
	 */
	static Mat4f translation(float x, float y, float z);

	/**
	 * \brief Returns a matrix which performs a rotation around the x axis.
	 * \param angle The rotation angle.
	 * \return The rotation matrix.
	 */
	static Mat4f rotationX(float angle);

	/**
	 * \brief Returns a matrix which performs a rotation around the y axis.
	 * \param angle The rotation angle.
	 * \return The rotation matrix.
	 */
	static Mat4f rotationY(float angle);


	/**
	 * \brief Returns a matrix which performs a rotation around the z axis.
	 * \param angle The rotation angle.
	 * \return The rotation matrix.
	 */
	static Mat4f rotationZ(float angle);

	/**
	 * \brief Returns a matrix which performs a rotation around all axis.
	 * \param angleX The rotation around the x-axis.
	 * \param angleY The rotation around the y-axis.
	 * \param angleZ The rotation around the z-axis.
	 * \return The rotation matrix.
	 */
	static Mat4f rotation(float angleX = 0.f, float angleY = 0.f, float angleZ = 0.f);

	/**
	 * \brief Returns a matrix which performs a uniform scaling.
	 * \param scale The scaling.
	 * \return The uniform scaling matrix.
	 */
	static Mat4f scale(float scale);

	/**
	 * \brief Returns a matrix which performs a scaling.
	 * \param xScale The scaling of the x-axis.
	 * \param yScale The scaling of the y-axis.
	 * \param zScale The scaling of the z-axis.
	 * \return The scaling matrix.
	 */
	static Mat4f scale(float xScale, float yScale, float zScale = 1.f);

	/* */
	/**
	 * \brief Returns a matrix which performs the perpective transformation.
	 * \param aspectRatio The aspect ratio.
	 * \param fov The field of view.
	 * \param near The near clipping plane.
	 * \param far The far clipping plane.
	 * \return The perspective transformation matrix.
	 */
	static Mat4f perspectiveTransformation(
		float aspectRatio = 1.f,
		float fov = 75.f,
		float near = 0.01f,
		float far = 1000.f
	);
};
