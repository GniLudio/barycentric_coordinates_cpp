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
	void Reset(void)
	{
		mouseMovement = Mat4f();
		triangle = Triangle(
			Vertex({ -500, 0 }, Colors::RED),
			Vertex({ 200, 200 }, Colors::GREEN),
			Vertex({ 300, -300 }, Colors::BLUE)
		);
		barycentric = Barycentric(1 / 3.f, 1 / 3.f, 1 / 3.f);
		pointColor = Colors::WHITE;
		pointSize = 10.f;

		onlyInside = true;
		currently_dragging = -1;

		displayIsolines = true;
		isolineStart = 0.f;
		isolineEnd = 1.f;
		isolineInterval = 1.f;


		UpdatePoint(-1);
	}
private:
	Mat4f mouseMovement;

	Triangle triangle;
	Barycentric barycentric;
	Vec4f point, pointColor;

	int currently_dragging;
	bool displayIsolines, onlyInside;
	float pointSize;
	float isolineStart, isolineInterval, isolineEnd;

	CircleDrawer circleDrawer;
	LineDrawer lineDrawer;
public:
	BarycentricCoordinates(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imguiStyle = ImGui::StyleColorsClassic)
		: Window("Barycentric Coordinates", width, height, fontSize, imguiStyle)
	{
		Reset();
	}

	void Update() override
	{
		glClearColor(0, 0, 0, 1.f);
		this->CheckInputs();
		this->UpdateUI();
		this->Draw();
	}
private:
	/**
	 * \brief Keeps the point inside the triangle and updates the barycentric coordinates.
	 */
	void KeepInside()
	{
		point = triangle.closest(point);
		barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Updates the point according to the barycentric coordinates and the triangle.
	 * \param changedAxis The changed barycentric coordinate so the sum stays at 1. (-1 for no balancing)
	 */
	void UpdatePoint(int changedAxis)
	{
		// balances the barycentric coordinates if needed
		if (changedAxis != -1)
		{
			float change = 1.f - (barycentric[0] + barycentric[1] + barycentric[2]);
			change /= 2.f;
			for (int i=0; i<3; i++)
			{
				if (i != changedAxis && i)
				{
					barycentric[i] += change;
				}
			}
		}
		point = triangle.calculatePoint(barycentric);
		if (onlyInside) 
			this->KeepInside();
	}

	/**
	 * \brief Updates the barycentric coordinates according to the triangle and point positions.
	 */
	void UpdateBarycentric(void)
	{
		if (onlyInside)
			this->KeepInside();
		else
			barycentric = Barycentric(triangle[0].position, triangle[1].position, triangle[2].position, point);
	}

	/**
	 * \brief Handles user inputs.
	 */
	void CheckInputs(void)
	{
		if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
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
		else
		{
			Utilities::ApplyMouseMovement(mouseMovement, ImGuiMouseButton_Left);
		}
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
		// settings menu
		UserInterface::BeginSettingsMenu(*this);

		if (UserInterface::AddCollapsingHeader("Triangle"))
		{
			ImGui::Indent();
			char* labels[3] = { "A", "B", "C" };
			for (int i = 0; i < 3; i++)
			{
				if (UserInterface::DragVec(&triangle[i].position[0], labels[i], 2))
					UpdatePoint(-1);
			}
			ImGui::Unindent();
		}

		ImGui::Spacing();

		if (UserInterface::AddCollapsingHeader("Barycentric Coordinates"))
		{
			ImGui::Indent();
			if (ImGui::Checkbox("Only Inside", &onlyInside))
				UpdateBarycentric();
			if (ImGui::IsItemHovered(0))
				ImGui::SetTooltip("Keyboard Shortcut: 'I'");
			char* labels[4] = { "Alpha", "Beta", "Gamma", "None" };
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
			ImGui::Checkbox("Display Isolines", &displayIsolines);
			if (ImGui::IsItemHovered(0))
				ImGui::SetTooltip("Keyboard Shortcut: 'L'");
			ImGui::DragFloat("Start", &isolineStart, 0.1f, -2.f, isolineEnd -0.1f, "%.1f");
			ImGui::DragFloat("End", &isolineEnd, 0.1f, isolineStart +0.1f, 3.f, "%.1f");
			ImGui::DragFloat("Interval", &isolineInterval, 0.01f, 0.01f, 1.f, "%.2f");
			ImGui::Unindent();
		}

		if (ImGui::Button("Reset")) Reset();
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Keyboard Shortcut: 'R'");

		ImGui::End();

		// info menu
		UserInterface::BeginInfoMenu(*this);
		ImGui::BeginDisabled();
		UserInterface::DragVec(&barycentric[0], "Barycentric");
		ImGui::EndDisabled();
		ImGui::End();

	}

	/**
	 * \brief Draws the image.
	 */
	void Draw(void)
	{
		Mat4f iWindowMat = Mat4f::scale(2.f / getWidth(), 2.f / getHeight(), 0);
		Mat4f modelMatrix = iWindowMat * mouseMovement;

		Mesh({ triangle }).render(modelMatrix);
		if (displayIsolines)
		{
			float l = (float) (getWidth() + getHeight()) * 10.f;
			Vec4f ab = (triangle[1].position - triangle[0].position).normalized() * l;
			Vec4f ac = (triangle[2].position - triangle[0].position).normalized()* l;
			Vec4f bc = (triangle[2].position - triangle[1].position).normalized()* l;
			for (float i = isolineStart; i <= isolineEnd; i += std::max(isolineInterval,0.01f))
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

