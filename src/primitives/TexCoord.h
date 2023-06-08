#pragma once

/**
 * \brief The texture coordinates.
 */
struct TexCoord
{
	/**
	 * \brief The u component.
	 */
	float u;

	/**
	 * \brief The v component.
	 */
	float v;

	/**
	 * \brief The constructor.
	 * \param u The u component.
	 * \param v The v component.
	 */
	TexCoord(float u=0.0f, float v=0.0f)
		: u(u), v(v)
	{
	}

	/**
	 * \brief Prints the texture coordinates.
	 * \param os The output strea.
	 * \param texCoord The texture coordinates.
	 * \return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, TexCoord texCoord)
	{
		os << "UV(" << texCoord.u << ", " << texCoord.v << ")";
		return os;
	}
};