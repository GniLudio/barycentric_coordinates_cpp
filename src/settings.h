#pragma once
#include "primitives/Triangle.h"
#include "utilities/Colors.h"
#include "imgui.h"
#include "math/Vec4f.h"

/**
 * \brief Several settings that are used as the initial values.
 */
namespace Settings
{
	// Window
	constexpr int window_width = 1600;
	static const int window_height = 900;
	static const float font_size = 24.0f;
	static void (*imgui_style)(ImGuiStyle*) = ImGui::StyleColorsClassic; // Classic, Light, Dark
	static const bool enable_vsync = false;
	static const Vec4f background_color = Vec4f(0.1f, 0.1f, 0.1f, 1);

	// UI
	static const float menu_width = 250.f;
	static const float ui_margin = 10.f;

	// Controls
	static const float mouse_rotation_speed = 0.005f;
	static const float mouse_zoom_speed = 0.05f;

	// Barycentric Coordinates
	static const Triangle triangle = Triangle(
		Vertex({ -500, 0 }, Colors::RED),
		Vertex({ 200, 200 }, Colors::GREEN),
		Vertex({ 300, -300 }, Colors::BLUE)
	);
	static const Barycentric barycentric = Barycentric(1 / 3.f, 1 / 3.f, 1 / 3.f);
	static const bool display_vertex_names = true;


	static const Vec4f point_color = Colors::WHITE;
	static const float point_size = 10.f;
	static const bool only_inside = false;

	static const bool display_isolines = false;
	static const float isoline_start = 0.f;
	static const float isoline_end = 1.f;
	static const float isoline_interval = 1.f;

	// Flicker Fusion
	static const float flicker_interval = 1.f;
	static const float flicker_brightness = 1.f;
	static const float gradient_height = -0.5f;
}