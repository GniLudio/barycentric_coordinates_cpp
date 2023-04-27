#pragma once

#include "math/Mat4f.h"

namespace Utilities
{

	void ApplyMouseMovement(Mat4f& mouseMovement, ImGuiMouseButton mouseButton, float rotationSpeed = 0.005f, float zoomSpeed = 0.05f)
	{
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;

			mouseMovement = Mat4f::rotationX(mouseDelta.y * rotationSpeed) * mouseMovement;
			mouseMovement = Mat4f::rotationY(mouseDelta.x * rotationSpeed) * mouseMovement;
		}

		if (0 != ImGui::GetIO().MouseWheel)
		{
			mouseMovement = Mat4f::scale(1 + (ImGui::GetIO().MouseWheel < 0 ? -zoomSpeed : zoomSpeed)) * mouseMovement;
		}

	}
}