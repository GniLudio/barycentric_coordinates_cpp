#pragma once

// Window class
#include "window/Window.h"

#include "settings.h"

class FlickerFusion : public Window
{
public:
	/**
	 * \brief The constructor.
	 */
	FlickerFusion() : Window("Flicker Fusion")
	{
		Reset();
	}

protected:
	/**
	 * \brief The update function.
	 */
	void update() override
	{
		const Vec4f bg_color = Settings::background_color;
		glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
		this->handle_inputs();
		this->update_ui();
		this->draw();
	}

private:
	/**
	 * \brief The start time.
	 * Updates when the interval is changed.
	 */
	double last_start_time;
	/**
	 * \brief The flicker interval.
	 */
	float flicker_interval;
	/**
	 * \brief The flicker brightness.
	 */
	float flicker_brightness;
	/**
	 * \brief Wether to display the gradient.
	 */
	bool gradient_enable;
	/**
	 * \brief The gradient height.
	 */
	float gradient_height;

	/**
	 * \brief Resets all settings.
	 */
	void Reset(void)
	{
		flicker_interval = 1.f;
		flicker_brightness = 0.5f;
		gradient_height = -0.5f;
		last_start_time = glfwGetTime();
	}
private:
	/**
	 * \brief Handles user inputs.
	 */
	void handle_inputs(void)
	{
	}

	/**
	 * \brief Updates the ui.
	 */
	void update_ui(void)
	{
		// settings menu
		UserInterface::BeginSettingsMenu(*this);
		if (UserInterface::AddCollapsingHeader("Flicker Fusion"))
		{
			if (ImGui::DragFloat("Interval", &flicker_interval, 0.01f, 0.f, 3.f))
				last_start_time = glfwGetTime();
			ImGui::DragFloat("Brightness", &flicker_brightness, 0.01f, 0.f, 1.f);
		}
		if (UserInterface::AddCollapsingHeader("Brightness Gradient"))
		{
			ImGui::Indent();
			ImGui::Checkbox("Show Gradient", &gradient_enable);
			ImGui::DragFloat("Height", &gradient_height, 0.001f, -1.f, 1.f);

			ImGui::Unindent();
		}
		ImGui::End();
	}

	/**
	 * \brief Draws the image.
	 */
	void draw(void)
	{
		const Mat4f model_matrix = Mat4f();

		float flicker_bottom = -1.f;
		if (gradient_enable)
		{
			// draws the gradient
			const Mesh gradient_mesh = Mesh({
				Triangle(
					Vertex({ -1.f, gradient_height }, Colors::WHITE), // left top
					Vertex({ -1.f, -1.f}, Colors::WHITE), // left bottom
					Vertex({ 1.f, gradient_height}, Colors::BLACK) // right top
				),
				Triangle(
					Vertex({ -1.f, -1.f}, Colors::WHITE), // left bottom
					Vertex({ 1.f, gradient_height}, Colors::BLACK), // right top
					Vertex({ 1.f, -1.f}, Colors::BLACK) // right bottom
				)
			});
			gradient_mesh.render(model_matrix);

			flicker_bottom = gradient_height;
		}

		const double time = glfwGetTime() - last_start_time;
		if (time > 0.25 && (int)(time / (double) flicker_interval) % 2 == 0)
		{
			// draws the flicker
			const Vec4f flicker_color = Colors::WHITE * flicker_brightness;
			const Mesh flicker_mesh = Mesh({
				Triangle(
					Vertex({ -1.f, 1.f }, flicker_color), // left top
					Vertex({ -1.f, flicker_bottom}, flicker_color), // left bottom
					Vertex({ 1.f, 1.f}, flicker_color) // right top
				),
				Triangle(
					Vertex({ -1.f, flicker_bottom}, flicker_color), // left bottom
					Vertex({ 1.f, 1.f}, flicker_color), // right top
					Vertex({ 1.f, flicker_bottom}, flicker_color) // right bottom
				)
			});
			flicker_mesh.render(model_matrix);
		}
	}
};