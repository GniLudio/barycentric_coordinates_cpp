#pragma once

// Window class
#include "window/Window.h"

// Colors
#include "utilities/Colors.h"

// Math classes
#include "math/Vec4f.h"
#include "rendering/Mesh.h"

class BarycentricCoordinates : public Window
{
	Mesh mesh = Mesh("teapot/teapot_scaled.obj");
	float rotationX = 0, rotationY = 0, viewDistance = 5.f;
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imgui_style = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imgui_style)
	{
	}

	void Update() override
	{
		if (ImGui::IsKeyDown(ImGuiKey_LeftShift) && ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::GetIO().WantCaptureMouse)
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;

			rotationX -= mouseDelta.y * 0.01f;
			rotationY -= mouseDelta.x * 0.01f;
		}
		if (ImGui::GetIO().MouseWheel != 0)
		{
			viewDistance *= ImGui::GetIO().MouseWheel > 0 ? 0.9f : 1.1f;
		}

		float aspectRatio = (float) getWidth() / (float) getHeight();
		Mat4f modelMatrix;
		modelMatrix = modelMatrix * Mat4f::rotationX(rotationX);
		modelMatrix = modelMatrix * Mat4f::rotationY(rotationY);
		modelMatrix = Mat4f::translation(0, 0, viewDistance) * modelMatrix * Mat4f::translation(0, -1, 0);;
		mesh.render(modelMatrix);
	}
};

