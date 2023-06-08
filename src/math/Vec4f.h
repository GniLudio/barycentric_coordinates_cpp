#pragma once

/* Defines the threshold to which the difference between two components should be considered as equal: */
#define COMPARE_DELTA 0.0001f
#include <ostream>

/**
 * \brief A point or vector with 4 components.
 */
struct Vec4f
{
public:
	/**
	 * \brief The first component.
	 */
	float x;

	/**
	 * \brief The second component.
	 */
	float y;

	/**
	 * \brief The third component.
	 */
	float z;

	/**
	 * \brief The fourth component. (1 for points, 0 for vectors)
	 */
	float w;
public:
	/**
	 * \brief The constructor.
	 * \param x The first component.
	 * \param y The second component.
	 * \param z The third component.
	 * \param w The fourth component.
	 */
	Vec4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

	/**
	 * Constructor which creates a Vec4 with (data[0], data[1], data[2], data[3]).
	 */
	explicit Vec4f(float data[4]);
public:
	/**
	 * \brief Converts a vector to a point.
	 * \return The point.
	 */
	Vec4f toPoint(void) const;

	/**
	 * \brief Converts a point to a vector.
	 * \return The vector.
	 */
	Vec4f toVector(void) const;

public:
	/**
	 * \brief The length of the vector.
	 * \param dimensions The dimensions. (0-4)
	 * \return The length.
	 */
	float length(int dimensions = 3) const;

	/**
	 * \brief The squared length.
	 * \param dimensions The dimensions. (0-4)
	 * \return The squared length.
	 */
	float squaredLength(int dimensions = 3) const;

	/**
	 * \brief The distance from this point to another point.
	 * \param p The other point.
	 * \param dimensions The dimensions. (0-4)
	 * \return The distance.
	 */
	float distanceTo(Vec4f p, int dimensions = 3) const;

	/**
	 * \brief Returns the dot product of two vectors.
	 * \param vector The other vector.
	 * \return The dot product.
	 */
	float dot(Vec4f vector) const;

	/**
	 * \brief Returns the cross product of two vectors.
	 * \param vector The other vector.
	 * \return The cross product.
	 */
	Vec4f cross(Vec4f vector) const;

	/**
	 * \brief Returns the normalized vector.
	 * \param dimensions The dimensions. (0-4)
	 * \return The normalized vector.
	 */
	Vec4f normalized(int dimensions = 3) const;

	/**
	 * \brief Returns a point on a line (start + vector) to another point.
	 * \param start The start point of the line.
	 * \param point The other point.
	 * \return The closest point.
	 */
	Vec4f closest(Vec4f start, Vec4f point) const;

public:
	/**
	 * \brief Checks that the difference of each component is smaller or equal to 'COMPARE_DELTA'.
	 * \param v The other vector or point.
	 * \return Whether the other is equal.
	 */
	bool operator==(Vec4f v) const;

	/**
	 * \brief Checks if at least one component has a higher difference than 'COMPARE_DELTA'. 
	 * \param v The other point or vector.
	 * \return Wether the other is not equal.
	 */
	bool operator!=(Vec4f v) const;

	/**
	 * \brief Returns the negated point or vector.
	 * \return The negated point or vector.
	 */
	Vec4f operator-(void) const;

	/**
	 * \brief Returns the sum of a point and vector or two vectors.
	 * \param v The other point or vector.
	 * \return The sum.
	 */
	Vec4f operator+(Vec4f v) const;

	/**
	 * \brief Returns the subtraction of this point or vector and another point or vector.
	 * \param v The other point or vector.
	 * \return The subtraction.
	 */
	Vec4f operator-(Vec4f v) const;

	/**
	 * \brief Multiplies the x,y,z components with the scalar.
	 * \param scalar The scalar.
	 * \return The multiplied point or vector.
	 */
	Vec4f operator*(float scalar) const;

	/**
	 * \brief Divides the x,y,z components with the scalar.
	 * \param scalar The scalar.
	 * \return The divided point or vector.
	 */
	Vec4f operator/(float scalar) const;

	/**
	 * \brief Allows access to the individual components.
	 * \param i The index.
	 * \return The component.
	 */
	float& operator[](int i);

	/**
	 * \brief Allows access to the individual components.
	 * \param i The index.
	 * \return The component.
	 */
	float operator[](int i) const;

public:
	/**
	 * \brief Adds the given Vec4f to an output stream.
	 * \param os The output stream.
	 * \param v The point or vector.
	 * \return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, Vec4f v);

private:
	/**
	 * \brief Prints an error if this is not a point.
	 * \param method The method name for debugging.
	 */
	void checkIsPoint(const char* method) const;
	/**
	 * \brief Prints an error if this is not a vector.
	 * \param method The method name for debugging.
	 */
	void checkIsVector(const char* method) const;
	/**
	 * \brief Wether this is a point.
	 * \return Is this a point.
	 */
	bool isPoint() const;
	/**
	 * \brief Wether this is a vector.
	 * \return Is this a vector.
	 */
	bool isVector() const;
};
