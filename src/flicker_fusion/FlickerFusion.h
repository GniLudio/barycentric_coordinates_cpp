#pragma once

// Window class
#include "window/Window.h"

class FlickerFusion : public Window
{
public:
	/**
	 * \brief The constructor.
	 * \param width The initial window width.
	 * \param height The initial window height.
	 * \param fontSize The font size.
	 * \param imguiStyle The imgui style. (light, dark, classic)
	 */
	FlickerFusion(int width = 1280, int height = 720, float fontSize = 16.0f, ImGuiStyleFunction imguiStyle = ImGui::StyleColorsClassic)
		: Window("Flicker Fusion", width, height, fontSize, imguiStyle)
	{
		// disables vsync
		//glfwSwapInterval(0);
		Reset();
	}

protected:
	void Update() override
	{
		glClearColor(0, 0, 0, 1.f);

		this->CheckInputs();
		this->UpdateUI();
		this->Draw();
	}

private:
	void Reset(void)
	{
		flickerInterval = 1.f;
		flickerBrightness = 0.5f;
		gradientHeight = -0.5f;
		lastStartTime = glfwGetTime();
	}
	double lastStartTime;
	float flickerInterval;
	float flickerBrightness;
	bool showGradient;
	float gradientHeight;

private:
	void CheckInputs(void)
	{
		
	}

	void UpdateUI(void)
	{
		// settings menu
		UserInterface::BeginSettingsMenu(*this);
		ImGui::PushItemWidth(settingsMenuWidth);

		if (UserInterface::AddCollapsingHeader("Flicker Fusion"))
		{
			if (ImGui::DragFloat("Interval", &flickerInterval, 0.01f, 0.f, 3.f))
				lastStartTime = glfwGetTime();
			ImGui::DragFloat("Brightness", &flickerBrightness, 0.01f, 0.f, 1.f);
		}


		if (UserInterface::AddCollapsingHeader("Brightness Gradient"))
		{
			ImGui::Indent();
			ImGui::Checkbox("Show Gradient", &showGradient);
			ImGui::DragFloat("Height", &gradientHeight, 0.001f, -1.f, 1.f);

			ImGui::Unindent();
		}

		ImGui::PopItemWidth();
		ImGui::End();
	}

	void Draw(void)
	{
		Mat4f modelMatrix = Mat4f();

		float flickerBottom = -1.f;
		if (showGradient)
		{
			Mesh mesh = Mesh({
				Triangle(
					Vertex({ -1.f, gradientHeight }, Colors::WHITE), // left top
					Vertex({ -1.f, -1.f}, Colors::WHITE), // left bottom
					Vertex({ 1.f, gradientHeight}, Colors::BLACK) // right top
				),
				Triangle(
					Vertex({ -1.f, -1.f}, Colors::WHITE), // left bottom
					Vertex({ 1.f, gradientHeight}, Colors::BLACK), // right top
					Vertex({ 1.f, -1.f}, Colors::BLACK) // right bottom
				)
			});
			mesh.render(modelMatrix);

			flickerBottom = gradientHeight;
		}

		double time = glfwGetTime() - lastStartTime;
		if (time > 0.25 && ((int)(time / (double) flickerInterval) % 2 == 0))
		{
			Vec4f flickerColor = Colors::WHITE * flickerBrightness;
			Mesh mesh = Mesh({
				Triangle(
					Vertex({ -1.f, 1.f }, flickerColor), // left top
					Vertex({ -1.f, flickerBottom}, flickerColor), // left bottom
					Vertex({ 1.f, 1.f}, flickerColor) // right top
				),
				Triangle(
					Vertex({ -1.f, flickerBottom}, flickerColor), // left bottom
					Vertex({ 1.f, 1.f}, flickerColor), // right top
					Vertex({ 1.f, flickerBottom}, flickerColor) // right bottom
				)
			});
			mesh.render(modelMatrix);
		}


	}
};