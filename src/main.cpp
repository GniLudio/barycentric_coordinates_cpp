#include <iostream>

#include "barycentric_coordinates/BarycentricCoordinates.h"

int main(int, char**)
{
	try
	{
		BarycentricCoordinates(1280, 720, 16.0f, ImGui::StyleColorsClassic).Start();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}


	return 0;
}
