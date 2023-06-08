#include <iostream>

#include "barycentric_coordinates/BarycentricCoordinates.h"

int main(int argc, char** argv)
{
	try
	{
		BarycentricCoordinates().start();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}