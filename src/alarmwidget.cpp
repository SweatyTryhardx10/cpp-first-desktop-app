#include <iostream>
#include <string>
#include <algorithm>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h> // Windows-specific generic mapping of something
#include "alarmwidget.h"

void AlarmWidget::Render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    // ImGui::SetNextWindowSizeConstraints(ImVec2(200, 200), ImVec2(500, 500)); // TODO: Attach callback in argument
    ImGui::Begin("Shutdown Timer", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::SliderFloat("##01", &vHour, 0, 12, "%.0f hours");
    ImGui::SliderFloat("##02", &vMinute, 5, 60, "%.0f mins.");
    ImGui::PopItemWidth();

    ImVec2 btnSize = ImGui::GetContentRegionAvail();
    // btnSize.y = std::clamp(btnSize.y, 40.0f, 100.0f);
    if (!commandIssued && ImGui::Button("Start Timer", btnSize))
    {
        int seconds = (vHour * 3600) + (vMinute * 60);
        const char* command = ("shutdown -s -t " + std::to_string(seconds)).c_str();
        system(command);

        commandIssued = true;
    }

    if (commandIssued && ImGui::Button("Clear Timer", btnSize))
    {
        const char *command = "shutdown -a";
        system(command);

        commandIssued = false;
    }

    ImGui::End();
}

void AlarmWidget::SetPosition(uint16_t x, uint16_t y)
{
    posX = x;
    posY = y;
}

void AlarmWidget::SetSize(uint16_t w, uint16_t h)
{
    size.x = w;
    size.y = h;

    std::cout << "Size set to: " << size.x << ", " << size.y << std::endl;
}