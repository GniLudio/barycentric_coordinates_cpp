#include "UserInterface.h"

#include <string>
#include "settings.h"

void UserInterface::begin_info_menu(const Window& window)
{
	ImGui::SetNextWindowPos(ImVec2(Settings::ui_margin, window.get_height() - Settings::ui_margin), 0, ImVec2(0.f, 1.f));
	ImGui::Begin("Info", nullptr,
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_AlwaysAutoResize
	);
	ImGui::PushItemWidth(Settings::menu_width);
}

void UserInterface::begin_settings_menu(const Window& window)
{
	ImGui::SetNextWindowPos(ImVec2(window.get_width() - Settings::ui_margin, Settings::ui_margin), 1, ImVec2(1.f, 0.f));
	ImGui::SetNextWindowCollapsed(true, ImGuiCond_Appearing);
	ImGui::Begin("Settings (S)", nullptr,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_AlwaysAutoResize
	);
	ImGui::PushItemWidth(Settings::menu_width);
	if (ImGui::IsKeyPressed(ImGuiKey_S, false))
		ImGui::SetWindowCollapsed(!ImGui::IsWindowCollapsed());
}

bool UserInterface::add_collapsing_header(const char* title)
{
	return ImGui::CollapsingHeader(title,
		ImGuiTreeNodeFlags_DefaultOpen |
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick
	);
}

void UserInterface::add_text(const char* text, Vec4f pos, Mat4f model_matrix, const Window& window)
{
	pos = model_matrix * pos;
	ImGui::SetNextWindowPos(ImVec2(pos.x + window.get_width() / 2.0f, -pos.y + window.get_height() / 2.f), 0, ImVec2(0.5f, 0.5f));
	ImGui::Begin(text, nullptr,
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBackground
	);
	ImGui::BeginDisabled();
	ImGui::TextColored(ImVec4(1,1,1,1), text);
	ImGui::EndDisabled();
	ImGui::End();

}

bool UserInterface::drag_vec(float* v, const char* label, int dimensions, float v_speed, float v_min, float v_max,
	const char* format, ImGuiSliderFlags flags)
{
	bool changed;
	if (dimensions == 2)
		changed = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags);
	else if (dimensions == 3)
		changed = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags);
	else if (dimensions == 4)
		changed = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags);
	else
		throw std::invalid_argument("UserInterface::drag_vec can only be called with dimensions between 2-4.");
	return changed;
}

bool UserInterface::drag_color(float* color, const char* label, bool alpha)
{
	if (alpha) 
		return ImGui::ColorEdit4(label, color);
	return ImGui::ColorEdit3(label, color);
}

bool UserInterface::drag_mat(float* matrix_data, const char* label, int dimensions, bool disabled, float v_speed, float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{

	bool edited = false;
	if (add_collapsing_header(label)) {
		ImGui::Indent();
		const float total_width = ImGui::GetColumnWidth();
		const float dummy_width = 5.f;
		const float total_dummy_width = dummy_width * (dimensions - 1);
		const float drag_width = (total_width - total_dummy_width) / dimensions;
		if (disabled) ImGui::BeginDisabled();
		ImGui::PushItemWidth(drag_width);
		for (int y = 0; y < dimensions; y++) {
			for (int x = 0; x < dimensions; x++) {
				std::string s = "##" + std::to_string(y) + "x" + std::to_string(x);
				edited |= ImGui::DragFloat(s.c_str(), &matrix_data[x*4 + y], v_speed, v_min, v_max, format, flags);
				if (x != dimensions - 1) {
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(-15.f + dummy_width, 0));
					ImGui::SameLine();
				}
			}
		}
		ImGui::PopItemWidth();
		if (disabled) 
			ImGui::EndDisabled();
		ImGui::Unindent();
	}
	return edited;

}

bool UserInterface::add_tooltip(const char* text, ImVec4 color)
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
