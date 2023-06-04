#pragma once

/* Defines the threshold to which the difference between two components should be considered as equal: */
#define COMPARE_DELTA 0.0001f
#include <ostream>

#include "imgui.h"

struct Vec4f
{
public:
	/** The x component */
	float x;

	/** The y component */
	float y;

	/** The z component */
	float z;

	/** The w component */
	float w;
public:
	/**
     * Constructor.
     *
     * Creates the origin (point) by default.
     */
	Vec4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

	/**
	 * Constructor which creates a Vec4 with (data[0], data[1], data[2], data[3]).
	 */
	Vec4f(float data[4]);
public:
	/**
	 * Converts a *vector* to a point.
	 */
	Vec4f toPoint(void) const;

	/**
	 * Converts a *point* to a vector.
	 */
	Vec4f toVector(void) const;

public:
	/** Returns the length of the *vector*. */
	float length(int dimensions = 3) const;

	/** Returns the squared length of the *vector*. */
	float squaredLength(int dimensions = 3) const;

	/** Returns the Euclidian distance from the *p* to the given *p*. */
	float distanceTo(Vec4f p, int dimensions = 3) const;

	/** Returns the dot product of this *v* with the given *v*. */
	float dot(Vec4f v) const;

	/** Returns the cross v of this *v* with the given *v*. */
	Vec4f cross(Vec4f v) const;

	/** Returns the normalized vector of this *vector*. */
	Vec4f normalized(int dimensions = 3) const;

	/** Returns the closest point from a point to this *vector*. */
	Vec4f closest(Vec4f start, Vec4f point);

public:
	/** Checks that the difference of each component is smaller or equal to 'COMPARE_DELTA'. */
	bool operator==(Vec4f v) const;

	/** Checks if at least one component has a higher difference than 'COMPARE_DELTA'. */
	bool operator!=(Vec4f v) const;

	/** Returns this *vector* negated. */
	Vec4f operator-(void) const;

	/** Returns the sum of two vectors. */
	Vec4f operator+(Vec4f v) const;

	/** Returns the subtraction of two vectors. */
	Vec4f operator-(Vec4f v) const;

	/** Returns the vector where the x, y and z components of this *vector* are multiplied by the s. */
	Vec4f operator*(float s) const;

	/** Returns the vector where the x, y and z components of this *vector* are divided by the s. */
	Vec4f operator/(float s) const;

	/** Allows access to the individual components. */
	float& operator[](int i);

	/** Allows access to the individual components. */
	float operator[](int i) const;

public:
	/**
	 * Adds the given Vec4f to an output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, Vec4f vector);

private:
	/** Checks whether the vector is a point. (w = 1) */
	void checkIsPoint(char* method) const;
	/** Checks whether the vector is a vector. (w = 0) */
	void checkIsVector(char* method) const;
	/** Whether the vector is a point. (w=1) */
	bool isPoint() const;
	/** Whether the vector is a vector. (w=0) */
	bool isVector() const;
};
