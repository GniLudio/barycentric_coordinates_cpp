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
	Vec4f point, pointColor;

	int currently_dragging = -1;

	void Reset(void)
	{
		mouseMovement = Mat4f();
		triangle = Triangle(
			Vertex({-300, 0}, Colors::RED),
			Vertex({400, 350}, Colors::GREEN),
			Vertex({300, -300}, Colors::BLUE)
		);
		barycentric = Barycentric(1 / 3.f, 1 / 3.f, 1/3.f);
		pointColor = Colors::WHITE;
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
		Mat4f iWindowMat = Mat4f::scale(2 / windowSize.x, 2 / windowSize.y, 1 / (windowSize.x + windowSize.y));
		Mat4f modelMatrix = mouseMovement * iWindowMat;

		// clears the color
		glClearColor(0, 0, 0, 1.f);

		// mouse movement
		if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
		{
			Vec4f* points[4] = {&triangle[0].position, &triangle[1].position, &triangle[2].position, &point};
			if (Utilities::MoveWithMouse(points, 4, mouseMovement, ImGuiMouseButton_Left, currently_dragging))
			{
				switch (currently_dragging)
				{
				case 0:
				case 1:
				case 2:
					UpdatePoint();
				case 3:
					UpdateBarycentric();
				}
			}
		} else
		{
			Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);
		}


		// settings window
		UserInterface::BeginSettingsMenu(*this);
		if (UserInterface::AddCollapsingHeader("Triangle"))
		{
			char* labels[3] = { "A", "B", "C" };
			for (int i=0; i<3; i++)
			{
				if (UserInterface::DragVec(&triangle[i].position[0], labels[i]))
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
			if (UserInterface::DragVec(&point[0], "Point"))
				UpdateBarycentric();
		}
		if (UserInterface::AddCollapsingHeader("Colors"))
		{
			char* labels[3] = { "A", "B", "C" };
			for (int i = 0; i < 3; i++)
			{
				if (UserInterface::DragColor(&triangle[i].color[0], labels[i]))
					UpdatePoint();
			}
			UserInterface::DragColor(&pointColor[0], "Point");
		}
		if (ImGui::Button("Reset")) Reset();
		if (ImGui::Button("Reset Mouse Movement")) mouseMovement = Mat4f();
		ImGui::End();


		// info menu
		UserInterface::BeginInfoMenu(*this);
		ImGui::BeginDisabled();
		UserInterface::DragVec(&barycentric[0], "Barycentric");
		ImGui::EndDisabled();
		ImGui::End();

		// draw the image
		Mesh mesh = Mesh({ triangle });
		mesh.render(modelMatrix);
		CircleDrawer circleDrawer;
		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			Vec4f mousePos = Utilities::GetMousePosition();
			point = mouseMovement.inverse() * mousePos;
		}
		circleDrawer.draw( point, 5, pointColor, modelMatrix);
	}
private:
	void UpdatePoint(void)
	{
		point = triangle[0].position * barycentric[0]
			+ (triangle[1].position * barycentric[1]).toVector()
			+ (triangle[2].position * barycentric[2]).toVector();
	}

	void UpdateBarycentric(void)
	{
		barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}
};

