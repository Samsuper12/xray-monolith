#pragma once
#include <imgui/imgui.h>

static bool ugly_hack = false;
static ::std::string imgui_text_buffer;

inline LPCSTR ImGui_GetVersion()
{
	return ImGui::GetVersion();
}

inline void ImGui_SetNextWindowPos(Fvector2& pos)
{
	ImGui::SetNextWindowPos(*(ImVec2*)&pos, 0, *(ImVec2*)&Fvector2().set(0, 0));
}

inline void ImGui_SetNextWindowPos(Fvector2& pos, ImGuiCond cond)
{
	ImGui::SetNextWindowPos(*(ImVec2*)&pos, cond, *(ImVec2*)&Fvector2().set(0,0));
}

inline void ImGui_SetNextWindowPos(Fvector2& pos, ImGuiCond cond, Fvector2& pivot)
{
	ImGui::SetNextWindowPos(*(ImVec2*)&pos, cond, *(ImVec2*)&pivot);
}

inline void ImGui_SetNextWindowSize(Fvector2& size, ImGuiCond cond = 0)
{
	ImGui::SetNextWindowSize(*(ImVec2*)&size, cond);
}

inline void ImGui_SetNextWindowSizeConstraints(Fvector2& size_min, Fvector2& size_max)
{
	ImGui::SetNextWindowSizeConstraints(*(ImVec2*)&size_min, *(ImVec2*)&size_max);
}

inline void ImGui_SetNextWindowContentSize(Fvector2& size)
{
	ImGui::SetNextWindowContentSize(*(ImVec2*)&size);
}

inline void ImGui_SetNextWindowScroll(Fvector2& scroll)
{
	ImGui::SetNextWindowScroll(*(ImVec2*)&scroll);
}

inline Fvector2 ImGui_GetWindowPos()
{
	ImVec2 v = ImGui::GetWindowPos();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetWindowSize()
{
	ImVec2 v = ImGui::GetWindowSize();
	return *(Fvector2*)&v;
}

inline void ImGui_SetWindowPos(Fvector2& pos, ImGuiCond cond = 0)
{
	ImGui::SetWindowPos(*(ImVec2*)&pos, cond);
}

inline void ImGui_SetWindowSize(Fvector2& size, ImGuiCond cond = 0)
{
	ImGui::SetWindowSize(*(ImVec2*)&size, cond);
}

inline void ImGui_SetWindowCollapsed(bool collapsed)
{
	ImGui::SetWindowCollapsed(collapsed);
}

inline void ImGui_SetScrollFromPosX(float pos)
{
	ImGui::SetScrollFromPosX(pos);
}

inline void ImGui_SetScrollFromPosY(float pos)
{
	ImGui::SetScrollFromPosY(pos);
}

inline Fvector2 ImGui_GetCursorScreenPos()
{
	ImVec2 iv = ImGui::GetCursorScreenPos();
	return *(Fvector2*)&iv;
}

inline void ImGui_SetCursorScreenPos(Fvector2& pos)
{
	ImGui::SetCursorScreenPos(*(ImVec2*)&pos);
}

inline Fvector2 ImGui_GetContentRegionAvail()
{
	ImVec2 v = ImGui::GetContentRegionAvail();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetCursorPos()
{
	ImVec2 v = ImGui::GetCursorPos();
	return *(Fvector2*)&v;
}

inline void ImGui_SetCursorPos(Fvector2& pos)
{
	ImGui::SetCursorPos(*(ImVec2*)&pos);
}

inline Fvector2 ImGui_GetCursorStartPos()
{
	ImVec2 v = ImGui::GetCursorStartPos();
	return *(Fvector2*)&v;
}

inline void ImGui_SameLine()
{
	ImGui::SameLine();
}

inline void ImGui_SameLine(float offset)
{
	ImGui::SameLine(offset);
}

inline void ImGui_Dummy(Fvector2& size)
{
	ImGui::Dummy(*(ImVec2*)&size);
}

inline void ImGui_TextDisabled(LPCSTR text)
{
	ImGui::TextDisabled(text, 0);
}

inline void ImGui_TextWrapped(LPCSTR text)
{
	ImGui::TextWrapped(text, 0);
}

inline void ImGui_TextColored(Fcolor& col, LPCSTR text)
{
	ImGui::TextColoredV(ImVec4{ col.r, col.g, col.b, col.a }, text, 0);
}

inline void ImGui_LabelText(LPCSTR label, LPCSTR text)
{
	ImGui::LabelText(label, text, 0);
}

inline void ImGui_BulletText(LPCSTR text)
{
	ImGui::BulletText(text, 0);
}

inline bool ImGui_Button(LPCSTR label)
{
	return ImGui::Button(label, *(ImVec2*)&Fvector2().set(80,22));
}

inline bool ImGui_Button(LPCSTR label, Fvector2 size)
{
	return ImGui::Button(label, *(ImVec2*)&size);
}

inline bool ImGui_InvisibleButton(LPCSTR label)
{
	return ImGui::InvisibleButton(label, *(ImVec2*)&Fvector2().set(80,22), 0);
}

inline bool ImGui_InvisibleButton(LPCSTR label, Fvector2 size)
{
	return ImGui::InvisibleButton(label, *(ImVec2*)&size, 0);
}

inline bool ImGui_InvisibleButton(LPCSTR label, Fvector2 size, ImGuiButtonFlags flags)
{
	return ImGui::InvisibleButton(label, *(ImVec2*)&size, flags);
}

inline void ImGui_ProgressBar(float fraction, Fvector2 size = Fvector2{flt_max,0}, LPCSTR overlay = 0)
{
	ImGui::ProgressBar(fraction, *(ImVec2*)&size, overlay);
}

inline bool ImGui_DragFloat2(LPCSTR name, Fvector2& vec, float speed = 1.f, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::DragFloat2(name, (float*)&vec, speed, min, max, format, flags);
}

inline bool ImGui_DragFloat3(LPCSTR name, Fvector& vec, float speed = 1.f, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::DragFloat3(name, (float*)&vec, speed, min, max, format, flags);
}

inline bool ImGui_DragFloat4(LPCSTR name, Fvector4& vec, float speed = 1.f, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::DragFloat4(name, (float*)&vec, speed, min, max, format, flags);
}

inline bool ImGui_ColorPicker3(LPCSTR name, Fcolor& color, ImGuiColorEditFlags flags = 0)
{
	return ImGui::ColorPicker3(name, (float*)&color, flags);
}

inline bool ImGui_ColorPicker4(LPCSTR name, Fcolor& color, ImGuiColorEditFlags flags = 0)
{
	return ImGui::ColorPicker4(name, (float*)&color, flags);
}

inline bool ImGui_ColorEdit3(LPCSTR name, Fcolor& color, ImGuiColorEditFlags flags = 0)
{
	return ImGui::ColorEdit3(name, (float*)&color, flags);
}

inline bool ImGui_ColorEdit4(LPCSTR name, Fcolor& color, ImGuiColorEditFlags flags = 0)
{
	return ImGui::ColorEdit4(name, (float*)&color, flags);
}

inline bool ImGui_SliderFloat2(LPCSTR name, Fvector2& vec, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::SliderFloat2(name, (float*)&vec, min, max, format, flags);
}

inline bool ImGui_SliderFloat3(LPCSTR name, Fvector& vec, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::SliderFloat3(name, (float*)&vec, min, max, format, flags);
}

inline bool ImGui_SliderFloat4(LPCSTR name, Fvector4& vec, float min = 0.f, float max = 0.f, LPCSTR format = "%.3f", ImGuiSliderFlags flags = 0)
{
	return ImGui::SliderFloat4(name, (float*)&vec, min, max, format, flags);
}

inline LPCSTR ImGui_InputText(LPCSTR label, LPCSTR text, int capacity = 100, ImGuiInputTextFlags flags = 0, bool& changed = ugly_hack)
{
	imgui_text_buffer = (text && xr_strlen(text)) ? text : "";
	changed = ImGui::InputText(label, (char*)imgui_text_buffer.c_str(), capacity, flags);
	return imgui_text_buffer.c_str();
}

inline LPCSTR ImGui_InputTextMultiline(LPCSTR label, LPCSTR text, int capacity = 100, Fvector2 size = Fvector2{ 0,0 }, ImGuiInputTextFlags flags = 0, bool& changed = ugly_hack)
{
	imgui_text_buffer = (text && xr_strlen(text)) ? text : "";
	changed = ImGui::InputTextMultiline(label, (char*)imgui_text_buffer.c_str(), capacity, *(ImVec2*)&size, flags);
	return imgui_text_buffer.c_str();
}

inline LPCSTR ImGui_InputTextWithHint(LPCSTR label, LPCSTR hint, LPCSTR text, int capacity = 100, ImGuiInputTextFlags flags = 0, bool& changed = ugly_hack)
{
	imgui_text_buffer = (text && xr_strlen(text)) ? text : "";
	changed = ImGui::InputTextWithHint(label, hint, (char*)imgui_text_buffer.c_str(), capacity, flags);
	return imgui_text_buffer.c_str();
}

inline bool ImGui_CollapsingHeader(LPCSTR label)
{
	return ImGui::CollapsingHeader(label);
}

inline bool ImGui_CollapsingHeader(LPCSTR label, bool* visible)
{
	return ImGui::CollapsingHeader(label, visible);
}

inline bool ImGui_InputFloat2(LPCSTR name, Fvector2& vec, LPCSTR format = "%.3f", ImGuiInputTextFlags flags = 0)
{
	return ImGui::InputFloat2(name, (float*)&vec, format, flags);
}

inline bool ImGui_InputFloat3(LPCSTR name, Fvector& vec, LPCSTR format = "%.3f", ImGuiInputTextFlags flags = 0)
{
	return ImGui::InputFloat3(name, (float*)&vec, format, flags);
}

inline bool ImGui_InputFloat4(LPCSTR name, Fvector4& vec, LPCSTR format = "%.3f", ImGuiInputTextFlags flags = 0)
{
	return ImGui::InputFloat4(name, (float*)&vec, format, flags);
}

inline bool ImGui_ColorButton(LPCSTR name, Fcolor& color, ImGuiColorEditFlags flags = 0, Fvector2 size = Fvector2{ 0,0 })
{
	return ImGui::ColorButton(name, *(ImVec4*)&color, flags, *(ImVec2*)&size);
}

inline bool ImGui_Selectable(LPCSTR name, bool selected, ImGuiSelectableFlags flags = 0, Fvector2 size = Fvector2{ 0,0 })
{
	return ImGui::Selectable(name, selected, flags, *(ImVec2*)&size);
}

inline bool ImGui_BeginMenu(LPCSTR name)
{
	return ImGui::BeginMenu(name, true);
}

inline bool ImGui_BeginListBox(LPCSTR name, Fvector2 size = Fvector2{ 0,0 })
{
	return ImGui::BeginListBox(name, *(ImVec2*)&size);
}

inline void ImGui_SetTooltip(LPCSTR text)
{
	ImGui::SetTooltip(text, 0);
}

inline void ImGui_SetItemTooltip(LPCSTR text)
{
	ImGui::SetItemTooltip(text, 0);
}

inline void ImGui_OpenPopup(LPCSTR name)
{
	ImGui::OpenPopup(name);
}

inline void ImGui_OpenPopup(ImGuiID id)
{
	ImGui::OpenPopup(id);
}

inline bool ImGui_IsPopupOpen(LPCSTR name)
{
	return ImGui::IsPopupOpen(name);
}

inline bool ImGui_BeginTable(LPCSTR name, int colums, ImGuiTableFlags flags = 0, Fvector2 size = Fvector2{ 0,0 }, float width = 0)
{
	return ImGui::BeginTable(name, colums, flags, *(ImVec2*)&size, width);
}

inline void ImGui_TableSetBgColor(ImGuiTableBgTarget target, Fcolor& color, int column_n = -1)
{
	ImGui::TableSetBgColor(target, color.get(), column_n);
}

inline void ImGui_BeginDisabled()
{
	ImGui::BeginDisabled(true);
}

inline void ImGui_PushClipRect(Fvector2 min, Fvector2 max, bool intersect)
{
	ImGui::PushClipRect(*(ImVec2*)&min, *(ImVec2*)&max, intersect);
}

inline Fvector2 ImGui_GetItemRectMin()
{
	ImVec2 v = ImGui::GetItemRectMin();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetItemRectMax()
{
	ImVec2 v = ImGui::GetItemRectMax();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetItemRectSize()
{
	ImVec2 v = ImGui::GetItemRectSize();
	return *(Fvector2*)&v;
}

inline bool ImGui_IsKeyPressed(ImGuiKey key)
{
	return ImGui::IsKeyPressed(key, true);
}

inline LPCSTR ImGui_GetKeyName(ImGuiKey key)
{
	return ImGui::GetKeyName(key);
}

inline bool ImGui_Shortcut(ImGuiKeyChord keys)
{
	return ImGui::Shortcut(keys, 0);
}

inline Fvector2 ImGui_CalcTextSize(LPCSTR text, bool hide_after_double_hash = false, float wrap_width = -1.f)
{
	ImVec2 v = ImGui::GetItemRectSize();
	return *(Fvector2*)&v;
}

inline bool ImGui_IsMouseHoveringRect(Fvector2 min, Fvector2 max)
{
	return ImGui::IsMouseHoveringRect(*(ImVec2*)&min, *(ImVec2*)&max, true);
}

inline bool ImGui_IsMouseHoveringRect(Fvector2 min, Fvector2 max, bool clip)
{
	return ImGui::IsMouseHoveringRect(*(ImVec2*)&min, *(ImVec2*)&max, clip);
}

inline bool ImGui_IsMousePosValid(Fvector2 pos = {0,0})
{
	return ImGui::IsMousePosValid((ImVec2*)&pos);
}

inline Fvector2 ImGui_GetMousePos()
{
	ImVec2 v = ImGui::GetMousePos();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetMousePosOnOpeningCurrentPopup()
{
	ImVec2 v = ImGui::GetMousePosOnOpeningCurrentPopup();
	return *(Fvector2*)&v;
}

inline Fvector2 ImGui_GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_treshold = -1.f)
{
	ImVec2 v = ImGui::GetMouseDragDelta(button, lock_treshold);
	return *(Fvector2*)&v;
}

inline LPCSTR ImGui_GetClipboardText()
{
	return ImGui::GetClipboardText();
}

inline Fcolor ImGui_GetStyleColorVec4(ImGuiCol idx)
{
	return *(Fcolor*)&ImGui::GetStyleColorVec4(idx);
}

inline void ImGui_PushStyleVar(ImGuiStyleVar var,Fvector2 val)
{
	ImGui::PushStyleVar(var, *(ImVec2*)&val);
}

inline void ImGui_PopStyleVar()
{
	ImGui::PopStyleVar(1);
}

inline void ImGui_PushStyleColor(ImGuiCol idx, Fcolor& col)
{
	ImGui::PushStyleColor(idx, *(ImVec4*)&col);
}

inline void ImGui_PopStyleColor()
{
	ImGui::PopStyleColor(1);
}

inline void ImGui_PushFont(LPCSTR name)
{
	// TODO: imgui fonts
	//ImGui::PushFont(Device.imgui().GetFont(name));
}