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

class BarycentricCoordinates : public Window
{
public:
	/**
	 * \brief The constructor.
	 * \param width The initial window width.
	 * \param height The initial window height.
	 * \param fontSize The font size.
	 * \param imguiStyle The imgui style. (light, dark, classic)
	 */
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imguiStyle = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imguiStyle)
	{
		Reset();
	}
protected:
	/**
	 * \brief The update method. (Called each frame)
	 */
	void Update(void) override
	{
		glClearColor(0, 0, 0, 1.f);
		this->CheckInputs();
		this->UpdateUI();
		this->Draw();
	}

private:
	void Reset(void)
	{
		triangle = Triangle(
			Vertex({ -500, 0 }, Colors::RED),
			Vertex({ 200, 200 }, Colors::GREEN),
			Vertex({ 300, -300 }, Colors::BLUE)
		);
		barycentric = Barycentric(1 / 3.f, 1 / 3.f, 1 / 3.f);
		UpdatePoint(-1);
		pointColor = Colors::WHITE;
		pointSize = 10.f;

		onlyInside = true;
		currently_dragging = -1;

		displayIsolines = false;
		isolineStart = -1.f;
		isolineEnd = 1.f;
		isolineInterval = 1.f;

		mouseZoom = 1.f;
		mouseRotationX = 0.f;
		mouseRotationY = 0.f;
	}
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
	 * \brief The point.
	 * Is updated when the barycentric coordinates or the triangle gets changed.
	 */
	Vec4f point;
	/**
	 * \brief The point color.
	 */
	Vec4f pointColor;
	/**
	 * \brief The point size.
	 */
	float pointSize;
	/**
	 * \brief Whether the point needs to be inside the triangle.
	 */
	bool onlyInside;
	/**
	 * \brief Which point is currently being dragged.
	 * Keeps dragging the same point until the mouse is released.
	 */
	int currently_dragging;
	/**
	 * \brief Whether the isolines should be displayed
	 */
	bool displayIsolines;
	/// <summary>
	/// Setting which isolines should be displayed.
	/// </summary>
	float isolineStart, isolineInterval, isolineEnd;
	/// <summary>
	/// Setting for the mouse movement.
	/// </summary>
	float mouseZoom, mouseRotationX, mouseRotationY;
private:
	/**
	 * \brief Keeps the point inside the triangle and updates the barycentric coordinates.
	 */
	void KeepInside(void)
	{
		point = triangle.closest(point);
		barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Returns the mouse movement matrix.
	 * \return The mouse movement.
	 */
	Mat4f getMouseMovement(void)
	{
		return Mat4f::scale(mouseZoom) * Mat4f::rotation(mouseRotationX, mouseRotationY);
	}

	/**
	 * \brief Updates the point according to the barycentric coordinates and the triangle.
	 * \param changedBarycentric Which barycentric coordinate was modified. (-1 if no balancing is needed)
	 */
	void UpdatePoint(int changedBarycentric)
	{
		// balances the barycentric coordinates if needed
		if (changedBarycentric != -1)
		{
			float change = 1.f - (barycentric[0] + barycentric[1] + barycentric[2]);
			for (int i=0; i<3; i++)
				if (i != changedBarycentric && i)
					barycentric[i] += change / 2.f;
		}
		// updates the point
		point = triangle.calculatePoint(barycentric);
		// keeps the point inside
		if (onlyInside) this->KeepInside();
	}

	/**
	 * \brief Updates the barycentric coordinates according to the triangle and point positions.
	 */
	void UpdateBarycentric(void)
	{
		// keeps the point inside (and updates the barycentric coordinates)
		if (onlyInside) 
			this->KeepInside();
		// updates the barycentric coordinates
		else
			barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Handles user inputs.
	 */
	void CheckInputs(void)
	{
		Mat4f mouseMovement = getMouseMovement();
		// zoom with mouse wheel
		Utilities::UpdateMouseZoom(mouseZoom);
		// rotate with with shift + left click
		if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
		{
			Utilities::UpdateMouseRotation(mouseRotationX, mouseRotationY, ImGuiMouseButton_Left);
		}
		// move points with left click
		else
		{
			Vec4f* points[4] = { &triangle[0].position, &triangle[1].position, &triangle[2].position, &point };
			if (Utilities::MoveWithMouse(points, 4, mouseMovement, ImGuiMouseButton_Left, currently_dragging))
			{
				switch (currently_dragging)
				{
				case 0:
				case 1:
				case 2:
					UpdatePoint(-1);
					break;
				case 3:
					UpdateBarycentric();
					break;
				default:
					break;
				}
			}
		}

		// keyboard shortcuts
		if (ImGui::IsKeyPressed(ImGuiKey_L, false))
		{
			displayIsolines = !displayIsolines;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_I, false))
		{
			onlyInside = !onlyInside;
			UpdateBarycentric();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_R, false))
			Reset();
	}

	/**
	 * \brief Updates the User Interface.
	 */
	void UpdateUI(void)
	{
		Mat4f mouseMovement = getMouseMovement();

		// settings menu
		UserInterface::BeginSettingsMenu(*this);
		ImGui::PushItemWidth(settingsMenuWidth);

		Mat4f temp;
		if (UserInterface::AddCollapsingHeader("Triangle"))
		{
			ImGui::Indent();
			char* labels[3] = { "A", "B", "C" };
			for (int i = 0; i < 3; i++)
				if (UserInterface::DragVec(&triangle[i].position[0], labels[i], 2))
					UpdatePoint(-1);
			ImGui::Unindent();
		}
		ImGui::Spacing();

		if (UserInterface::AddCollapsingHeader("Barycentric Coordinates"))
		{
			ImGui::Indent();
			if (ImGui::Checkbox("Only Inside (I)", &onlyInside))
				UpdateBarycentric();
			UserInterface::AddTooltip("Keyboard Shortcut: 'I'");
			char* labels[4] = { "", "Beta", "Gamma", "None" };
			char* labels2[3] = { "Alpha", "Beta", "Gamma" };
			for (int i = 0; i < 3; i++)
			{
				if (onlyInside)
				{
					if (ImGui::DragFloat(labels2[i], &barycentric[i], 0.01f, 0.f, 1.f))
						UpdatePoint(i);
				}
				else {
					if (ImGui::DragFloat(labels2[i], &barycentric[i], 0.01f))
						UpdatePoint(i);
				}
			}
			if (UserInterface::DragVec(&point[0], "Point", 2))
				UpdateBarycentric();
			ImGui::Unindent();
		}

		ImGui::Spacing();

		if (UserInterface::AddCollapsingHeader("Isolines"))
		{
			ImGui::Indent();
			ImGui::Checkbox("Display Isolines (L)", &displayIsolines);
			UserInterface::AddTooltip("Keyboard Shortcut: 'L'");
			ImGui::DragFloat("Start", &isolineStart, 0.1f, 0, 0,"%.1f");
			ImGui::DragFloat("End", &isolineEnd, 0.1f, 0, 0, "%.1f");
			ImGui::DragFloat("Interval", &isolineInterval, 0.01f, 0, 0, "%.2f");
			UserInterface::AddTooltip("Values between -0.01 and 0.01 are ignored.");
			ImGui::Unindent();
		}

		if (ImGui::Button("Reset (R)")) Reset();
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

	Vec4f infiniteVector(Vec4f vector, Mat4f modelMatrix)
	{
		Vec4f temp = modelMatrix * vector;

		Vec4f result = Vec4f(vector);
		result.z = 0;
		result = result * (getWidth() / temp.x) * (getHeight() / temp.y);

		return result;
	}

	/**
	 * \brief Draws the image.
	 */
	void Draw(void)
	{
		Mat4f mouseMovement = getMouseMovement();
		Mat4f iWindowMat = Mat4f::scale(2.f / getWidth(), 2.f / getHeight(), 0);
		Mat4f modelMatrix = iWindowMat * mouseMovement;

		CircleDrawer circleDrawer;
		LineDrawer lineDrawer;

		Mesh({ triangle }).render(modelMatrix);
		if (displayIsolines && std::abs(isolineInterval) >= 0.01f)
		{
			Vec4f ab = infiniteVector(triangle[1].position - triangle[0].position, modelMatrix);
			Vec4f ac = infiniteVector(triangle[2].position - triangle[0].position, modelMatrix);
			Vec4f bc = infiniteVector(triangle[2].position - triangle[1].position, modelMatrix);
			for (float i = isolineStart; i <= isolineEnd; i += isolineInterval)
			{
				float other = (1.f - i) / 2.f;
				// alpha
				Vec4f p = triangle.calculatePoint(Barycentric(i, other, other));
				lineDrawer.draw(p, p + bc, Colors::BLUE, modelMatrix);
				lineDrawer.draw(p, p - bc, Colors::BLUE, modelMatrix);
				// beta
				p = triangle.calculatePoint(Barycentric(other, i, other));
				lineDrawer.draw(p, p + ac, Colors::GREEN, modelMatrix);
				lineDrawer.draw(p, p - ac, Colors::GREEN, modelMatrix);
				// gamma
				p = triangle.calculatePoint(Barycentric(other, other, i));
				lineDrawer.draw(p, p + ab, Colors::RED, modelMatrix);
				lineDrawer.draw(p, p - ab, Colors::RED, modelMatrix);
			}
		}
		circleDrawer.draw(point, pointSize, pointColor, modelMatrix);

	}
};

