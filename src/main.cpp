#include <iostream>

#include "barycentric_coordinates/BarycentricCoordinates.h"
#include "flicker_fusion/FlickerFusion.h"

int main(int argc, char** argv)
{
	try
	{
		//BarycentricCoordinates(1600, 900, 24.0f, ImGui::StyleColorsLight).Start();
		FlickerFusion(1600, 900, 24.0f, ImGui::StyleColorsLight).Start();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}


	return 0;
}

int WinMain(int argc, char** argv)
{
	main(argc, argv);
}