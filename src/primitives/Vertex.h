#pragma once

#include "math/Vec4f.h"
#include "TexCoord.h"

struct Vertex
{
	/** The position. */
	Vec4f position;

	/** The normal. */
	Vec4f normal;

	/** The color. */
	Vec4f color;

	/** The uv coordinates. */
	TexCoord uv;

	Vertex(Vec4f position = {}, Vec4f color = {1,1,1}, Vec4f normal = { 0,0,0,0 }, TexCoord uv = {0,0})
		: position(position), normal(normal), color(color), uv(uv)
	{
	}
};