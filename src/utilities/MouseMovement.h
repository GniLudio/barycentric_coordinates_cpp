#pragma once

#include <vector>

#include "math/Mat4f.h"

namespace Utilities
{
	/**
	 * Applies rotation and zoom with mouse controls.
	 *
	 * @param mouseMovement The movement matrix.
	 * @param mouseButton The rotation button.
	 * @param rotationSpeed The rotation speed.
	 * @param zoomSpeed The zoom speed.
	 */
	inline bool ApplyMouseMovement(Mat4f& mouseMovement, ImGuiMouseButton mouseButton, float rotationSpeed = 0.005f, float zoomSpeed = 0.05f)
	{
		bool changed = false;
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;

			mouseMovement = Mat4f::rotationX(mouseDelta.y * rotationSpeed) * mouseMovement;
			mouseMovement = Mat4f::rotationY(mouseDelta.x * rotationSpeed) * mouseMovement;
			changed = true;
		}

		if (0 != ImGui::GetIO().MouseWheel)
		{
			mouseMovement = Mat4f::scale(1 + (ImGui::GetIO().MouseWheel < 0 ? -zoomSpeed : zoomSpeed)) * mouseMovement;
			changed = true;
		}
		return changed;
	}

	/**
	 * Returns the current mouse position.
	 */
	inline Vec4f GetMousePosition()
	{
		ImVec2 imMousePos = ImGui::GetIO().MousePos;
		imMousePos.y = ImGui::GetIO().DisplaySize.y - imMousePos.y;
		imMousePos.x -= ImGui::GetIO().DisplaySize.x / 2.f;
		imMousePos.y -= ImGui::GetIO().DisplaySize.y / 2.f;

		return {imMousePos.x, imMousePos.y, 0};
	}

	inline int FindNearest(Vec4f* points[], int pointCount, Vec4f pos)
	{
		int iNearest = 0;
		for (int i=1; i<pointCount; i++)
		{
			if (points[i]->distanceTo(pos) < points[iNearest]->distanceTo(pos))
			{
				iNearest = i;
			}
		}
		return iNearest;
	}

	/**
	 * Mouses the nearest point with the mouse.
	 *
	 * @param points The points.
	 * @param pointCount The point count.
	 * @param modelMatrix The model matrix that is applied to the points.
	 * @param mouseButton The mouse button.
	 * @param currently_dragging Which point is being dragged.
	 */
	inline bool MoveWithMouse(Vec4f* points[], int pointCount, Mat4f modelMatrix, ImGuiMouseButton mouseButton, int& currently_dragging)
	{
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			// gets the current mouse position
			// TODO: project mouse position onto plane
			Vec4f mousePos = modelMatrix.inverse() * GetMousePosition();

			// if no point is being dragged already
			if (currently_dragging == -1)
			{
				// find the nearest point
				currently_dragging = FindNearest(points, pointCount, mousePos);
			}
			// updates the point position
			*points[currently_dragging] = mousePos;
			return true;
		}
		currently_dragging = -1;
		return false;
	}




}