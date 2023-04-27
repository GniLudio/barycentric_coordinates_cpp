#pragma once

#include "math/Mat4f.h"

namespace Utilities
{

	void ApplyMouseMovement(Mat4f& mouseMovement, ImGuiMouseButton mouseButton, float speed = 0.005f)
	{
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;

			mouseMovement = Mat4f::rotationX(mouseDelta.y * speed) * mouseMovement;
			mouseMovement = Mat4f::rotationY(mouseDelta.x * speed) * mouseMovement;
		}

		return;
		if (0 != ImGui::GetIO().MouseWheel)
		{
			//mouseMovement.scale*= ImGui::GetIO().MouseWheel < 0 ? 0.9f : 1.1f;
		}

	}
}