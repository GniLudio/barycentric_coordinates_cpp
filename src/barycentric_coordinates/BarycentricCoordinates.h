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

	Triangle triangle;
	Barycentric barycentric;
	Vec4f point;

	int currently_dragging = -1;

	void Reset(void)
	{
		mouseMovement = Mat4f::scale(2);
		triangle = Triangle(
			Vertex({-300, 0}, Colors::RED),
			Vertex({400, 350}, Colors::GREEN),
			Vertex({300, -300}, Colors::BLUE)
		);
		barycentric = Barycentric(1 / 3.f, 1 / 3.f, 1/3.f);
		UpdatePoint();
	}
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imguiStyle = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imguiStyle)
	{
		Reset();
	}

	void Update() override
	{
		// preparations
		Vec4f windowSize = { (float)getWidth(), (float)getHeight(), (getWidth() + getHeight()) / 2.f};
		Mat4f iWindowMat = Mat4f::scale(windowSize.x, windowSize.y, windowSize.y).inverse() * 2;
		Mat4f modelMatrix = mouseMovement * iWindowMat;

		// clears the color
		glClearColor(0, 0, 0, 1.f);

		// mouse movement
		Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);


		// settings window
		UserInterface::BeginSettingsMenu(*this);
		/*
		if (UserInterface::AddCollapsingHeader("Triangle"))
		{
			char* labels[3] = { "A", "B", "C" };
			for (int i=0; i<3; i++)
			{
				if (UserInterface::DragVec4f(triangle[i].position, labels[i]))
					UpdatePoint();
			}
		}
		if (UserInterface::AddCollapsingHeader("Barycentric Coordinates"))
		{
			char* labels[3] = { "Alpha", "Beta", "Gamma" };
			for (int i = 0; i < 3; i++)
			{
				if (ImGui::DragFloat( labels[i], &barycentric[i], 0.01f))
					UpdatePoint();
			}
		}
		*/
		ImGui::BeginDisabled();
		UserInterface::DragMat4f(mouseMovement, "Mouse Movement");
		ImGui::EndDisabled();
		UserInterface::DragVec4f(point, "P");
		if (ImGui::Button("Reset")) Reset();
		ImGui::End();

		// draw the image
		Mesh mesh = Mesh({ triangle });
		mesh.render(modelMatrix);
		CircleDrawer circleDrawer;
		circleDrawer.draw( point, 50, Colors::RED, mouseMovement, windowSize);
	}
private:
	void UpdatePoint(void)
	{
		point = triangle[0].position * barycentric[0]
			+ (triangle[1].position * barycentric[1]).toVector()
			+ (triangle[2].position * barycentric[2]).toVector();
	}
};

