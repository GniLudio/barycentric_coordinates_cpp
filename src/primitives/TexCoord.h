#pragma once

struct TexCoord
{
	/** The u component. */
	float u;

	/** The v component. */
	float v;

	TexCoord(float u=0.0f, float v=0.0f)
		: u(u), v(v)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, TexCoord texCoord)
	{
		os << "UV(" << texCoord.u << ", " << texCoord.v << ")";
		return os;
	}
};