#pragma once

// Window class
#include "window/Window.h"

// Utilities
#include "utilities/Colors.h"
#include "utilities/MouseMovement.h"
#include "utilities/UserInterface.h"

// Math classes
#include "rendering/Mesh.h"

class BarycentricCoordinates : public Window
{
	Mesh mesh = Mesh("teapot/teapot_scaled.obj");
	Mat4f mouseMovement;
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imgui_style = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imgui_style)
	{
	}

	void Update() override
	{
		Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);
		mesh.render(mouseMovement);
	}
};

