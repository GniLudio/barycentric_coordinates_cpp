#pragma once

#include "math/Mat4f.h"
#include "math/Vec4f.h"
#include "window/Window.h"
#include "imgui.h"

namespace UserInterface
{
	/**
	 * \brief Starts an imgui menu that can be used to displaying information.
	 * \param window The window.
	 */
	void begin_info_menu(const Window& window);

	/**
	 * \brief Starts an imgui menu that can be used for displaying settings.
	 * \param window The window.
	 */
	void begin_settings_menu(const Window& window);

	/**
	 * \brief Adds an imgui header which can be collapsed.
	 * \param title The title.
	 * \return Whether it isn't collapsed.
	 */
	bool add_collapsing_header(const char* title);

	/**
	 * \brief Adds text to a position.
	 * \param text The text.
	 * \param pos The position.
	 * \param model_matrix The model matrix.
	 * \param window The window.
	 */
	void add_text(const char* text, Vec4f pos, Mat4f model_matrix, const Window& window);

	/**
	 * \brief Displays a vector with imgui.
	 * \param v The vector.
	 * \param label The label.
	 * \param dimensions The number of dimensions.
	 * \param v_speed The drag speed.
	 * \param v_min The minimum value.
	 * \param v_max The maximum value.
	 * \param format The formatting.
	 * \param flags The slider flags.
	 * \return Whether the vector was changed.
	 */
	bool drag_vec(float* v, const char* label, int dimensions = 3,
	              float v_speed = (1.0f), float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * \brief Displays a color with imgui.
	 * \param color The color.
	 * \param label The label.
	 * \param alpha Whether to display the alpha value.
	 * \return Whether the color was changed.
	 */
	bool drag_color(float* color, const char* label, bool alpha = false);

	/**
	 * \brief Displays a matrix with imgui.
	 * \param matrix_data The matrix data.
	 * \param label The label.
	 * \param dimensions The number of dimensions.
	 * \param disabled Whether the matrix can be modified.
	 * \param v_speed The drag speed.
	 * \param v_min The minimum value.
	 * \param v_max The maximum value.
	 * \param format The formatting.
	 * \param flags The slider flags.
	 * \return Whether the matrix was changed.
	 */
	bool drag_mat(float* matrix_data, const char* label, int dimensions = 4, bool disabled = false, float v_speed = (1.0f),
	              float v_min = (0.0f), float v_max = (0.0f), const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * \brief Adds a tooltip when hovering over the last widget.
	 * \param text The text.
	 * \param color The text color.
	 * \return Whether the tooltip was displayed.
	 */
	bool add_tooltip(const char* text, ImVec4 color = ImVec4(0.5f, 0.5f, 0.5f, 1));
}
