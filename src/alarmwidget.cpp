#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <d3d11.h>
#include <ctime>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "alarmwidget.h"
#include "numberdialwidget.h"

const std::string filename = "alarm_data.txt";

void AlarmWidget::Render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    // ImGui::SetNextWindowSizeConstraints(ImVec2(200, 200), ImVec2(500, 500)); // TODO: Attach callback in argument
    ImGui::Begin("Shutdown Timer", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    float sliderWidth = ImGui::GetContentRegionAvail().x * 0.48f;
    // ImGui::VSliderFloat("##AlarmHourSlider", ImVec2(sliderWidth, 100), &vHour, 0, 12, "%.0f hours");
    // ImGui::SameLine();
    // ImGui::VSliderFloat("##AlarmMinuteSlider", ImVec2(sliderWidth, 100), &vMinute, 5, 60, "%.0f mins.");
    hourDial->Render("Hours");
    minuteDial->Render("Minutes");
    
    ImVec2 btnSize = ImGui::GetContentRegionAvail();
    btnSize.y = std::clamp(btnSize.y, 40.0f, 100.0f);
    if (!commandIssued && ImGui::Button("Start Timer", btnSize))
    {
        // Schedule shutdown time on system
        int seconds = (vHour * 3600) + (vMinute * 60);
        ScheduleShutdownTime(seconds);

        // Save shutdown timestamp to file (for when the app is restarted)
        time_t systemTime = time(&systemTime);
        systemTime += seconds; // Add shutdown delay to current timestamp
        struct tm localTime = *localtime(&systemTime);
        SaveShutdownTime(localTime);
    }

    if (commandIssued && ImGui::Button("Clear Timer", btnSize))
    {
        ClearShutdownTime();
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
}

bool AlarmWidget::ScheduleShutdownTime(uint32_t seconds)
{
    const char *command = ("shutdown -s -t " + std::to_string(seconds)).c_str();
    int cmdOutput = system(command);
    
    if (cmdOutput == -1)
    {
        std::cout << "Error: " << strerror(errno) << std::endl;
        return false;
    }
    
    //TODO: How do I make sure that the scheduled shutdown corresponds to the one set by this application?

    commandIssued = true;
    return true;
}

/// @param shutdownTime The system time at which the shutdown should start.
/// @return Whether the shutdown was succesfully scheduled.
bool AlarmWidget::SaveShutdownTime(struct tm shutdownTime)
{
    // Initialized file
    std::ofstream outfile(filename);

    // CHECK: File not open.
    if (!outfile.is_open())
    {
        std::cout << "File (" << filename << ") is not open.";
        return false;
    }
    // CHECK: File not valid.
    if (!outfile.good())
    {
        std::cout << "File (" << filename << ") is invalid.";
        return false;
    }

    // Convert data to appropriate file-writing format
    std::string data[] = {
        std::to_string(shutdownTime.tm_sec),
        std::to_string(shutdownTime.tm_min),
        std::to_string(shutdownTime.tm_hour),
        std::to_string(shutdownTime.tm_mday),
        std::to_string(shutdownTime.tm_mon),
        std::to_string(shutdownTime.tm_year),
    };

    // Write data to file
    for (size_t i = 0; i < std::size(data); i++)
    {
        outfile << data[i] << std::endl;
    }

    // Close and save file changes
    outfile.close();

    return true;
}

void AlarmWidget::LoadShutdownTime()
{
    std::ifstream file(filename);

    // Reconstruct data from file
    struct tm dateTime;
    uint8_t line = 0;
    std::string data;
    while (getline(file, data))
    {
        // std::cout << "Data on line " + std::to_string(line) << ": " + data << std::endl;

        switch (line)
        {
        case 0: // Seconds
            dateTime.tm_sec = std::stoi(data);
            break;
        case 1: // Minutes
            dateTime.tm_min = std::stoi(data);
            break;
        case 2: // Minutes
            dateTime.tm_hour = std::stoi(data);
            break;
        case 3: // Minutes
            dateTime.tm_mday = std::stoi(data);
            break;
        case 4: // Minutes
            dateTime.tm_mon = std::stoi(data);
            break;
        case 5: // Minutes
            dateTime.tm_year = std::stoi(data);
            break;
        default:
            std::cout << "Unknown data present in " << filename << std::endl;
            break;
        }
        line++;
    }

    // Compute shutdown seconds from loaded data
    time_t shutdownTimestamp = mktime(&dateTime);
    int shutdownSeconds = shutdownTimestamp - time(NULL);

    // Schedule shutdown
    if (shutdownSeconds > 0)
        ScheduleShutdownTime(shutdownSeconds);
}

void AlarmWidget::ClearShutdownTime()
{
    const char *command = "shutdown -a";
    system(command);

    // Delete saved shutdown time
    // Source: https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    commandIssued = false;
}