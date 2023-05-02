#include <iostream>

#include "barycentric_coordinates/BarycentricCoordinates.h"

int main(int, char**)
{
	try
	{
		BarycentricCoordinates().Start();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}


	return 0;
}
