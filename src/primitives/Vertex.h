#pragma once

#include "math/Vec4f.h"
#include "TexCoord.h"

/**
 * \brief A vertex.
 */
struct Vertex
{
	/**
	 * \brief The position.
	 */
	Vec4f position;

	/**
	 * \brief The normal.
	 */
	Vec4f normal;

	/**
	 * \brief The color.
	 */
	Vec4f color;

	/**
	 * \brief The uv coordinates.
	 */
	TexCoord uv;

	/**
	 * \brief The constructor.
	 * \param position The position.
	 * \param color The color.
	 * \param normal The normal.
	 * \param uv The uv coordinates.
	 */
	Vertex(Vec4f position = {}, Vec4f color = {1,1,1}, Vec4f normal = { 0,0,0,0 }, TexCoord uv = {0,0})
		: position(position), normal(normal), color(color), uv(uv)
	{
	}
};