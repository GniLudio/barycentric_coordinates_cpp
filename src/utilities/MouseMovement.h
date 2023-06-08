#pragma once

#include "settings.h"
#include "math/Mat4f.h"

/**
 * \brief Several utilities.
 */
namespace Utilities
{
	/**
	 * \brief Updates the rotation with mouse movements.
	 * \param mouse_rotation_x The x rotation.
	 * \param mouse_rotation_y The y rotation.
	 * \param mouse_button The mouse button.
	 * \return Whether rotation was changed.
	 */
	inline bool update_rotation(float& mouse_rotation_x, float& mouse_rotation_y, ImGuiMouseButton mouse_button)
	{
		if (ImGui::IsMouseDown(mouse_button) && !ImGui::GetIO().WantCaptureMouse)
		{
			const ImVec2 mouse_delta = ImGui::GetIO().MouseDelta;
			mouse_rotation_x += mouse_delta.y * Settings::mouse_rotation_speed;
			mouse_rotation_y += mouse_delta.x * Settings::mouse_rotation_speed;
			return true;
		}
		return false;
	}

	/**
	 * \brief Updates the zoom with the mouse wheel.
	 * \param mouse_zoom The mouse zoom.
	 * \return Whether the zoom was changed.
	 */
	inline bool update_zoom(float& mouse_zoom)
	{
		if (0 != ImGui::GetIO().MouseWheel)
		{
			mouse_zoom *= 1 + (ImGui::GetIO().MouseWheel < 0 ? -Settings::mouse_zoom_speed : Settings::mouse_zoom_speed);
			return true;
		}
		return false;
	}

	/**
	 * \brief Returns the mouse position. (center = (0,0,0))
	 * \return The mouse position.
	 */
	inline Vec4f get_mouse_position()
	{
		ImVec2 im_mouse_pos = ImGui::GetIO().MousePos;
		// inverts the y axis
		im_mouse_pos.y = ImGui::GetIO().DisplaySize.y - im_mouse_pos.y;
		// centers the position
		im_mouse_pos.x -= ImGui::GetIO().DisplaySize.x / 2.f;
		im_mouse_pos.y -= ImGui::GetIO().DisplaySize.y / 2.f;

		return {im_mouse_pos.x, im_mouse_pos.y, 0};
	}

	/**
	 * \brief Find the nearest point from another point.
	 * \param points The points.
	 * \param point_count The point count.
	 * \param pos The other point.
	 * \param dimensions The number of dimensions.
	 * \return The nearest point index.
	 */
	inline int find_nearest(Vec4f* points[], int point_count, Vec4f pos, int dimensions)
	{
		// takes the last point first
		// so that the point in the barycentric coordinates demo has priority over the vertices
		int iNearest = point_count-1;
		for (int i=point_count-2; i>=0; i--)
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
	inline Vec4f project_onto_plane(Vec4f p0, Vec4f d, Vec4f n, Vec4f c)
	{
		const float t = (n.dot(c.toVector()) - n.dot(p0.toVector())) / n.dot(d);
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
	inline bool move_with_mouse(Vec4f* points[], int pointCount, Mat4f modelMatrix, ImGuiMouseButton mouseButton, int& currently_dragging)
	{
		if (ImGui::IsMouseDown(mouseButton) && !ImGui::GetIO().WantCaptureMouse)
		{
			Vec4f mousePos = modelMatrix.inverse() * get_mouse_position();
			mousePos = project_onto_plane(
				mousePos, 
				modelMatrix.inverse() * Vec4f(0, 0, 1, 0), 
				Vec4f(0, 0, -1, 0), 
				Vec4f()
			);
			if (currently_dragging == -1)
			{
				currently_dragging = find_nearest(points, pointCount, mousePos, 3);
			}
			*points[currently_dragging] = mousePos;
			return true;
		}
		currently_dragging = -1;
		return false;
	}

}