#include <iostream>
#include <string>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h> // Windows-specific generic mapping of something
#include "alarmwidget.h"

void AlarmWidget::Render()
{
    ImGui::SetNextWindowPos(ImVec2(400, 280), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Once);
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 200), ImVec2(500, 500)); // TODO: Attach callback in argument
    ImGui::Begin("Shutdown Timer");

    ImGui::SliderAngle("Alarm", &v_rad, -360.0F, 360.0F, "%.0f sec.");

    if (ImGui::Button("Start Timer", ImVec2(200, 40)) && !commandIssued)
    {
        int seconds = 60 * 60;
        const char* command = ("shutdown -s -t " + std::to_string(seconds)).c_str();
        std::cout << command;
        system(command);
        
        commandIssued = true;
    }
    if (ImGui::Button("Clear Timer", ImVec2(200, 40)))
    {
        const char* command = "shutdown -a";
        system(command);
    }

    ImGui::End();
}