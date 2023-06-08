#pragma once

// Window class
#include "window/Window.h"

// Primitives
#include "primitives/Barycentric.h"

// Utilities
#include "utilities/Colors.h"
#include "utilities/MouseMovement.h"
#include "utilities/UserInterface.h"

// Math classes
#include "rendering/CircleDrawer.h"
#include "rendering/LineDrawer.h"
#include "rendering/Mesh.h"

/**
 * \brief A demonstration of the barycentric coordinates.
 */
class BarycentricCoordinates : public Window
{
public:
	/**
	 * \brief The constructor.
	 */
	BarycentricCoordinates() : Window("Barycentric Coordinates")
	{
		reset();
	}
protected:
	/**
	 * \brief The update method. (Called each frame)
	 */
	void update(void) override
	{
		const Vec4f bg_color = Settings::background_color;
		glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
		this->handle_inputs();
		this->update_ui();
		this->draw();
	}
private:
	/**
	 * \brief The triangle.
	 * Can be moved with the mouse.
	 */
	Triangle triangle;

	/**
	 * \brief The barycentric coordinates.
	 * Is updated when the point gets moved.
	 */
	Barycentric barycentric;

	/**
	 * \brief Wether to display the vertex names.
	 */
	bool display_vertex_names;

	/**
	 * \brief The point.
	 * Is updated when the barycentric coordinates or the triangle gets changed.
	 */
	Vec4f point;

	/**
	 * \brief The point color.
	 */
	Vec4f point_color;

	/**
	 * \brief The point size.
	 */
	float point_size;

	/**
	 * \brief Whether the point needs to be inside the triangle.
	 */
	bool only_inside;

	/**
	 * \brief Which point is currently being dragged.
	 * Keeps dragging the same point until the mouse is released.
	 */
	int currently_dragging;

	/**
	 * \brief Whether the isolines should be displayed
	 */
	bool isolines_enabled;

	/// <summary>
	/// Setting which isolines should be displayed.
	/// </summary>
	float isolines_start, isolines_interval, isolines_end;

	/// <summary>
	/// Setting for the mouse movement.
	/// </summary>
	float mouse_zoom, mouse_rotation_x, mouse_rotation_y;

	const char* barycentric_labels[3] = {"Alpha", "Beta", "Gamma"};
	const Vec4f barycentric_colors[3] = {Colors::BLUE, Colors::GREEN, Colors::RED};

	/**
	 * \brief Resets all settings.
	 */
	void reset(void)
	{
		triangle = Settings::triangle;
		display_vertex_names = Settings::display_vertex_names;
		barycentric = Settings::barycentric;
		update_point(-1);
		point_color = Settings::point_color;
		point_size = Settings::point_size;

		only_inside = Settings::only_inside;
		currently_dragging = -1;

		isolines_enabled = Settings::display_isolines;
		isolines_start = Settings::isoline_start;
		isolines_end = Settings::isoline_end;
		isolines_interval = Settings::isoline_interval;

		mouse_zoom = 1.f;
		mouse_rotation_x = 0.f;
		mouse_rotation_y = 0.f;
	}
private:
	/**
	 * \brief Keeps the point inside the triangle and updates the barycentric coordinates.
	 */
	void keep_point_inside_triangle(void)
	{
		point = triangle.closest_in_triangle(point);
		barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Returns the mouse movement matrix.
	 * \return The mouse movement.
	 */
	Mat4f get_mouse_movement_matrix(void) const
	{
		return Mat4f::scale(mouse_zoom) * Mat4f::rotation(mouse_rotation_x, mouse_rotation_y);
	}

	/**
	 * \brief Updates the point according to the barycentric coordinates and the triangle.
	 * \param changed_barycentric Which barycentric coordinate was modified. (-1 if no balancing is needed)
	 */
	void update_point(int changed_barycentric)
	{
		// balances the barycentric coordinates if needed
		if (changed_barycentric != -1)
		{
			const float change = 1.f - (barycentric[0] + barycentric[1] + barycentric[2]);
			for (int i=0; i<3; i++)
			{
				if (i != changed_barycentric)
					barycentric[i] += change / 2.f;
			}
		}
		// updates the point
		point = triangle.calculate_point(barycentric);
		// keeps the point inside
		if (only_inside) 
			this->keep_point_inside_triangle();
	}

	/**
	 * \brief Updates the barycentric coordinates according to the triangle and point positions.
	 */
	void update_barycentric_coordinates(void)
	{
		// keeps the point inside (and updates the barycentric coordinates)
		if (only_inside) 
			this->keep_point_inside_triangle();
		// updates the barycentric coordinates
		else
			barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Handles user inputs.
	 */
	void handle_inputs(void)
	{
		const Mat4f mouse_movement = get_mouse_movement_matrix();
		// update zoom (with mouse wheel
		Utilities::update_zoom(mouse_zoom);
		// update rotation (with Shift + Left Mouse)
		if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
		{
			Utilities::update_rotation(mouse_rotation_x, mouse_rotation_y, ImGuiMouseButton_Left);
		}
		// update point position (with Left Mouse)
		else
		{
			Vec4f* points[4] = { &triangle[0].position, &triangle[1].position, &triangle[2].position, &point };
			if (Utilities::MoveWithMouse(points, 4, mouse_movement, ImGuiMouseButton_Left, currently_dragging))
			{
				switch (currently_dragging)
				{
				case 0:
				case 1:
				case 2:
					update_point(-1);
					break;
				case 3:
					update_barycentric_coordinates();
					break;
				default:
					break;
				}
			}
		}

		// keyboard shortcuts
		if (ImGui::IsKeyPressed(ImGuiKey_L, false))
		{
			isolines_enabled = !isolines_enabled;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_I, false))
		{
			only_inside = !only_inside;
			update_barycentric_coordinates();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_R, false))
			reset();
	}

	/**
	 * \brief Updates the User Interface.
	 */
	void update_ui(void)
	{
		const Mat4f mouse_movement = get_mouse_movement_matrix();

		// settings menu
		UserInterface::BeginSettingsMenu(*this);
		if (UserInterface::AddCollapsingHeader("Triangle"))
		{
			ImGui::Indent();
			ImGui::Checkbox("Show Names", &display_vertex_names);
			if (UserInterface::DragVec(&triangle[0].position.x, "A", 2))
				update_point(0);
			if (UserInterface::DragVec(&triangle[1].position.x, "B", 2))
				update_point(1);
			if (UserInterface::DragVec(&triangle[2].position.x, "B", 2))
				update_point(2);
			ImGui::Unindent();
		}
		ImGui::Spacing();
		if (UserInterface::AddCollapsingHeader("Barycentric Coordinates"))
		{
			ImGui::Indent();
			if (ImGui::Checkbox("Only Inside (I)", &only_inside))
				update_barycentric_coordinates();
			UserInterface::AddTooltip("Keyboard Shortcut: 'I'");
			for (int i = 0; i < 3; i++)
			{
				if (isolines_enabled)
				{
					Vec4f color = Colors::WHITE * 0.8f + barycentric_colors[i].toVector() * 0.2f;
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color.x, color.y, color.z, color.w));
				}
				if (only_inside)
				{
					if (ImGui::DragFloat(barycentric_labels[i], &barycentric[i], 0.01f, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
						update_point(i);
				}
				else {
					if (ImGui::DragFloat(barycentric_labels[i], &barycentric[i], 0.01f))
						update_point(i);
				}
				if (isolines_enabled)
					ImGui::PopStyleColor();
			}
			if (UserInterface::DragVec(&point[0], "Point", 2))
				update_barycentric_coordinates();
			ImGui::Unindent();
		}
		ImGui::Spacing();
		if (UserInterface::AddCollapsingHeader("Isolines"))
		{
			ImGui::Indent();
			ImGui::Checkbox("Show Isolines (L)", &isolines_enabled);
			UserInterface::AddTooltip("Keyboard Shortcut: 'L'");
			ImGui::DragFloat("Start", &isolines_start, 0.1f, 0, 0,"%.1f");
			ImGui::DragFloat("End", &isolines_end, 0.1f, 0, 0,"%.1f");
			ImGui::DragFloat("Interval", &isolines_interval, 0.01f, 0, 999.99f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
			UserInterface::AddTooltip("The isolines are not displayed for values between -0.01 and 0.01.");
			ImGui::Unindent();
		}
		ImGui::Spacing();
		if (ImGui::Button("Reset All (R)")) 
			reset();
		UserInterface::AddTooltip("Keyboard Shortcut: 'R'");
		ImGui::PopItemWidth();
		ImGui::End();

		// info menu
		UserInterface::BeginInfoMenu(*this);
		ImGui::BeginDisabled();
		// numbers near 0 and 1 are displays as 0 and 1
		Vec4f prettyBarycentric = Vec4f(barycentric[0], barycentric[1], barycentric[2]);
		for (int i=0; i<3; i++)
		{
			if (std::abs(1 - prettyBarycentric[i]) < COMPARE_DELTA) 
				prettyBarycentric[i] = 1.f;
			if (std::abs(prettyBarycentric[i]) < COMPARE_DELTA) 
				prettyBarycentric[i] = 0.f;
		}
		UserInterface::DragVec(&prettyBarycentric[0], "##Barycentric");
		ImGui::EndDisabled();
		ImGui::End();
	}

	/**
	 * \brief Returns a vector with a length that can cover the whole screen.
	 * \param direction The direction.
	 * \param modelMatrix The model matrix.
	 * \return The infinite vector.
	 */
	Vec4f get_infinite_vector(Vec4f direction, Mat4f modelMatrix) const
	{
		Vec4f temp = modelMatrix * direction;

		Vec4f result = direction;
		result.z = 0;
		result = result * (get_width() / temp.x) * (get_height() / temp.y);

		return result;
	}

	/**
	 * \brief Draws the image.
	 */
	void draw(void)
	{
		const Mat4f mouse_movement = get_mouse_movement_matrix();
		const Mat4f inverse_window = Mat4f::scale(2.f / get_width(), 2.f / get_height(), 0);
		const Mat4f model_matrix = inverse_window * mouse_movement;

		const CircleDrawer circle_drawer;
		const LineDrawer line_drawer;

		// draw triangle
		Mesh({ triangle }).render(model_matrix);
		// draw isolines
		if (isolines_enabled && std::abs(isolines_interval) >= 0.01f)
		{
			const Vec4f ab = get_infinite_vector(triangle[1].position - triangle[0].position, model_matrix);
			const Vec4f ac = get_infinite_vector(triangle[2].position - triangle[0].position, model_matrix);
			const Vec4f bc = get_infinite_vector(triangle[2].position - triangle[1].position, model_matrix);
			for (float i = isolines_start; i <= isolines_end; i += isolines_interval)
			{
				const float other = (1.f - i) / 2.f;
				// alpha
				Vec4f p = triangle.calculate_point(Barycentric(i, other, other));
				line_drawer.draw(p, p + bc, barycentric_colors[0], model_matrix);
				line_drawer.draw(p, p - bc, barycentric_colors[0], model_matrix);
				// beta
				p = triangle.calculate_point(Barycentric(other, i, other));
				line_drawer.draw(p, p + ac, barycentric_colors[1], model_matrix);
				line_drawer.draw(p, p - ac, barycentric_colors[1], model_matrix);
				// gamma
				p = triangle.calculate_point(Barycentric(other, other, i));
				line_drawer.draw(p, p + ab, barycentric_colors[2], model_matrix);
				line_drawer.draw(p, p - ab, barycentric_colors[2], model_matrix);
			}
		}
		circle_drawer.draw(point, point_size, point_color,model_matrix);
		if (display_vertex_names)
		{
			UserInterface::AddText("A", triangle[0].position, mouse_movement, *this);
			UserInterface::AddText("B", triangle[1].position, mouse_movement, *this);
			UserInterface::AddText("C", triangle[2].position, mouse_movement, *this);
		}

	}
};

