#pragma once

// Window class
#include "window/Window.h"

// Primitives
#include "primitives/Barycentric.h"

// Utilities
#include "utilities/Colors.h"
#include "utilities/MouseMovement.h"
#include "utilities/UserInterface.h"

// Math classes
#include "rendering/CircleDrawer.h"
#include "rendering/Mesh.h"

class BarycentricCoordinates : public Window
{
	Mat4f mouseMovement;
	Vec4f point, point2;
	int currently_dragging = -1;

	void Reset(void)
	{
		mouseMovement = Mat4f();
		point = {100, 200};
		point2 = {-100, -200};
	}
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imgui_style = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imgui_style)
	{
		Reset();
	}

	void Update() override
	{
		// preparations
		Vec4f windowSize = { (float)getWidth(), (float)getHeight() };

		// clears the color
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);

		// mouse movement
		if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
		{
			Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);
		} else
		{
			Vec4f* points[2] = {&point, &point2};
			Utilities::MoveWithMouse(points, 2, mouseMovement, ImGuiMouseButton_Left, currently_dragging);
		}

		// draws the image
		CircleDrawer circleDrawer;
		circleDrawer.draw(point, 25, Colors::RED, mouseMovement, windowSize, true, 5);
		circleDrawer.draw(point2, 25, Colors::GREEN, mouseMovement, windowSize, true, 5);
	}
};

