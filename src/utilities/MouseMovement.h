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
	inline bool UpdateMouseRotation(float& mouseRotationX, float& mouseRotationY,
		ImGuiMouseButton mouseButton, float rotationSpeed = 0.005f)
	{
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
			mouseRotationX += mouseDelta.y * rotationSpeed;
			mouseRotationY += mouseDelta.x * rotationSpeed;
			return true;
		}
		return false;
	}

	inline bool UpdateMouseZoom(float& mouseZoom, float zoomSpeed = 0.05f)
	{
		if (0 != ImGui::GetIO().MouseWheel)
		{
			mouseZoom *= 1 + (ImGui::GetIO().MouseWheel < 0 ? -zoomSpeed : zoomSpeed);
			return true;
		}
		return false;
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

	inline int FindNearest(Vec4f* points[], int pointCount, Vec4f pos, int dimensions)
	{
		int iNearest = pointCount-1;
		for (int i=pointCount-2; i>=0; i--)
		{
			if (points[i]->distanceTo(pos, dimensions) < points[iNearest]->distanceTo(pos, dimensions))
			{
				iNearest = i;
			}
		}
		return iNearest;
	}

	/**
	 * \brief Projects a points onto a plane.
	 * \param p0 The original point.
	 * \param d The direction onto the plane.
	 * \param n The normal of the plane.
	 * \param c A point on the plane.
	 * \return The projected point.
	 */
	inline Vec4f IntersectPlane(Vec4f p0, Vec4f d, Vec4f n, Vec4f c)
	{
		float t = (n.dot(c.toVector()) - n.dot(p0.toVector())) / (n.dot(d));
		return p0 + d * t;
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
			Vec4f mousePos = modelMatrix.inverse() * GetMousePosition();
			mousePos = IntersectPlane(
				mousePos, 
				modelMatrix.inverse() * Vec4f(0, 0, 1, 0), 
				Vec4f(0, 0, -1, 0), 
				Vec4f()
			);
			if (currently_dragging == -1)
			{
				currently_dragging = FindNearest(points, pointCount, mousePos, 3);
			}
			*points[currently_dragging] = mousePos;
			return true;
		}
		currently_dragging = -1;
		return false;
	}






}