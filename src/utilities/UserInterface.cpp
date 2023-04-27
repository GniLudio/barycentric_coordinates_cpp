#include "UserInterface.h"

#include <string>

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

void UserInterface::AddText(const char* text, Vec4f pos, const Window& window)
{
}

bool UserInterface::DragVec4f(Vec4f& v, const char* label, int depth, float v_speed, float v_min, float v_max,
	const char* format, ImGuiSliderFlags flags)
{
	if (depth == 2)
		return ImGui::DragFloat2(label, &v.x, v_speed, v_min, v_max, format, flags);
	else if (depth == 3)
		return ImGui::DragFloat3(label, &v.x, v_speed, v_min, v_max, format, flags);
	else if (depth == 4)
		return ImGui::DragFloat4(label, &v.x, v_speed, v_min, v_max, format, flags);
	else
		throw std::invalid_argument("UserInterface::DragVec4f can only be called with depth between 2-4.");

}

bool UserInterface::DragColor(Vec4f& color, const char* label, bool alpha)
{
	if (alpha) return ImGui::ColorEdit4(label, &color[0]);
	return ImGui::ColorEdit3(label, &color[0]);
}

bool UserInterface::DragMat4f(Mat4f& m, const char* label, int depth, bool disabled, float v_speed, float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{
	const float total_width = 380.f;
	const float dummy_width = 5;
	const float total_dummy_width = dummy_width * (depth - 1);
	const float drag_width = (total_width - total_dummy_width) / depth;
	bool edited = false;
	if (AddCollapsingHeader(label)) {
		if (disabled) ImGui::BeginDisabled();
		ImGui::PushItemWidth(drag_width);
		for (int y = 0; y < depth; y++) {
			for (int x = 0; x < depth; x++) {
				std::string s = "##" + std::to_string(y) + "x" + std::to_string(x);
				edited |= ImGui::DragFloat(s.c_str(), &m[x][y], v_speed, v_min, v_max, format, flags);
				if (x != depth - 1) {
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(-15.f + dummy_width, 0));
					ImGui::SameLine();
				}
			}
		}
		ImGui::PopItemWidth();
		if (disabled) ImGui::EndDisabled();
	}
	return edited;

}
