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
	Triangle triangle;
	Mat4f mouseMovement;
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imgui_style = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imgui_style)
	{
		Reset();
	}

	void Update() override
	{
		Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);

		UserInterface::BeginSettingsMenu(*this);
		if (UserInterface::AddCollapsingHeader("Triangle")) {
			ImGui::Indent();
			if (UserInterface::AddCollapsingHeader("Positions")) {
				UserInterface::DragVec4f(triangle[0].position, "A", 3, 0.01f, -0.5f, 0.5f);
				UserInterface::DragVec4f(triangle[1].position, "B", 3, 0.01f, -0.5f, 0.5f);
				UserInterface::DragVec4f(triangle[2].position, "C", 3, 0.01f, -0.5f, 0.5f);
			}
			if (UserInterface::AddCollapsingHeader("Colors")) {
				UserInterface::DragColor(triangle[0].color, "A");
				UserInterface::DragColor(triangle[1].color, "B");
				UserInterface::DragColor(triangle[2].color, "C");
			}
			ImGui::Unindent();
		}
		if (ImGui::Button("Reset")) Reset();
		ImGui::End();

		Mesh mesh({ triangle });

		mesh.render(mouseMovement);
	}

	void Reset(void) 
	{
		triangle = Triangle(
			Vertex(Vec4f(-0.5f, 0.25f), Colors::RED),
			Vertex(Vec4f(0.5f, 0.5f), Colors::GREEN),
			Vertex(Vec4f(0.5f, -0.5f), Colors::BLUE)
		);
		mouseMovement = Mat4f();
	}
};

