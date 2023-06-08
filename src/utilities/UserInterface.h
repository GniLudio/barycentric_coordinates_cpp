#pragma once

#include "math/Mat4f.h"
#include "math/Vec4f.h"
#include "window/Window.h"

namespace UserInterface
{
	/**
	 * Starts an imgui menu that can be used to displaying information.
	 */
	void BeginInfoMenu(const Window& window);

	/**
	 * Starts an imgui m enu that can be used for displaying settings.
	 */
	void BeginSettingsMenu(const Window& window);

	/*+
	 * Adds an imgui header which can be collapsed.
	 */
	bool AddCollapsingHeader(const char* title);

	/**
	 * Adds text at the position.
	 */
	void AddText(const char* text, Vec4f pos, Mat4f modelMatrix, const Window& window);

	/**
	 * Displays a vector with imgui.
	 */
	bool DragVec(float* v, const char* label, int depth = 3,
		float v_speed = (1.0f), float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * Displays a color with imgui.
	 */
	bool DragColor(float* color, const char* label, bool alpha = false);

	/**
	 * Displays a matrix with imgui.
	 */
	bool DragMat(float* m, const char* label, int depth = 4, bool disabled = false, float v_speed = (1.0f),
		float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * \brief Adds a tooltip when hovering over the last widget.
	 * \param text The text.
	 * \param color The text color.
	 * \return Whether the tooltip was displayed.
	 */
	bool AddTooltip(const char* text, ImVec4 color = ImVec4(0.5f, 0.5f, 0.5f, 1));

}
