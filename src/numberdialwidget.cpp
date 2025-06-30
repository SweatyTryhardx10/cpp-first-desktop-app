#include <iostream>
#include <string>
#include <d3d11.h>
#include <tchar.h> // Windows-specific generic mapping of something
#include <cmath>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "numberdialwidget.h"

bool NumberDialWidget::Render(const char *label)
{
    ImGui::PushID(label);
    ImGui::Text(label);
    
    ImVec2 p = ImGui::GetCursorScreenPos();

    ImGui::InvisibleButton(label, ImVec2(width, height));
    bool isActive = ImGui::IsItemActive();
    bool clicked = ImGui::IsItemClicked();

    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 center = ImVec2(p.x + width / 2.0f, p.y + height / 2.0f);
    ImVec2 localMousePos = ImVec2(mousePos.x - center.x, mousePos.y - center.y);

    if (isActive)
    {
        float radians = std::atan2(localMousePos.y, localMousePos.x);

        v = radians;
    }

    ImU32 baseColor = ImGui::GetColorU32(ImVec4(1.0f, 0.25f, 0.0f, 1.0f));

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    draw_list->AddEllipseFilled(center, ImVec2(width / 2, height / 2), baseColor, v, 20);
    
    // TODO: Draw an arc whose fill amount is modulated by the value (v)
    
    ImGui::PopID();
    
    return clicked;
}