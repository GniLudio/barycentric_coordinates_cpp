#include "UserInterface.h"

#include <string>
#include <iostream>

void UserInterface::BeginInfoMenu(const Window& window, float uiMargin)
{
	ImGui::SetNextWindowPos(ImVec2(uiMargin, window.getHeight() - uiMargin), 0, ImVec2(0.f, 1.f));
	ImGui::Begin("Info", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_AlwaysAutoResize
	);
}

void UserInterface::BeginSettingsMenu(const Window& window, float uiMargin)
{
	ImGui::SetNextWindowPos(ImVec2(window.getWidth() - uiMargin, uiMargin), 1, ImVec2(1.f, 0.f));
	ImGui::SetNextWindowCollapsed(true, ImGuiCond_Appearing);
	ImGui::Begin("Settings", nullptr,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_AlwaysAutoResize
	);
}

bool UserInterface::AddCollapsingHeader(const char* title)
{
	return ImGui::CollapsingHeader(title,
		ImGuiTreeNodeFlags_DefaultOpen |
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick
	);
}

void UserInterface::AddText(const char* text, Vec4f pos, Mat4f modelMatrix, const Window& window)
{
	pos = modelMatrix * pos;
	ImGui::SetNextWindowPos(ImVec2(pos.x + window.getWidth() / 2.0f, -pos.y + window.getHeight() / 2.f), 0, ImVec2(0.5f, 0.5f));
	ImGui::Begin(text, nullptr,
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBackground
	);
	ImGui::BeginDisabled();
	ImGui::TextColored(ImVec4(1,1,1,1),text);
	ImGui::EndDisabled();
	ImGui::End();

}

bool UserInterface::DragVec(float* v, const char* label, int depth, float v_speed, float v_min, float v_max,
	const char* format, ImGuiSliderFlags flags)
{
	bool changed;
	if (depth == 2)
		changed = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags);
	else if (depth == 3)
		changed = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags);
	else if (depth == 4)
		changed = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags);
	else
		throw std::invalid_argument("UserInterface::DragVec can only be called with depth between 2-4.");
	return changed;
}

bool UserInterface::DragColor(float* color, const char* label, bool alpha)
{
	if (alpha) return ImGui::ColorEdit4(label, color);
	return ImGui::ColorEdit3(label, color);
}

bool UserInterface::DragMat(float* m, const char* label, int depth, bool disabled, float v_speed, float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{

	bool edited = false;
	if (AddCollapsingHeader(label)) {
		ImGui::Indent();
		const float total_width = ImGui::GetColumnWidth();
		const float dummy_width = 5;
		const float total_dummy_width = dummy_width * (depth - 1);
		const float drag_width = (total_width - total_dummy_width) / depth;
		if (disabled) ImGui::BeginDisabled();
		ImGui::PushItemWidth(drag_width);
		for (int y = 0; y < depth; y++) {
			for (int x = 0; x < depth; x++) {
				std::string s = "##" + std::to_string(y) + "x" + std::to_string(x);
				edited |= ImGui::DragFloat(s.c_str(), &m[x*4 + y], v_speed, v_min, v_max, format, flags);
				if (x != depth - 1) {
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(-15.f + dummy_width, 0));
					ImGui::SameLine();
				}
			}
		}
		ImGui::PopItemWidth();
		if (disabled) ImGui::EndDisabled();
		ImGui::Unindent();
	}
	return edited;

}

bool UserInterface::AddTooltip(const char* text, ImVec4 color)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextColored(color, text);
		ImGui::EndTooltip();
		return true;
	}
	return false;
}
