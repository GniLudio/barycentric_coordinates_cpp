#pragma once

#include "math/Mat4f.h"
#include "math/Vec4f.h"
#include "window/Window.h"

namespace UserInterface
{
	/**
	 * Starts an imgui menu that can be used to displaying information.
	 */
	void BeginInfoMenu(const Window& window, float uiMargin = 10.0f);

	/**
	 * Starts an imgui m enu that can be used for displaying settings.
	 */
	void BeginSettingsMenu(const Window& window, float uiMargin = 10.0f);

	/*+
	 * Adds an imgui header which can be collapsed.
	 */
	bool AddCollapsingHeader(const char* title);

	/**
	 * Adds text at the position.
	 */
	void AddText(const char* text, Vec4f pos, const Window& window);

	/**
	 * 
	 */
	bool DragVec4f(Vec4f& v, const char* label, int depth = 3,
		float v_speed = (1.0f), float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 *
	 */
	bool DragColor(Vec4f& color, const char* label, bool alpha = false);

	/**
	 *
	 */
	bool DragMat4f(Mat4f& m, const char* label, int depth = 4, bool disabled = false, float v_speed = (1.0f),
		float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

}
