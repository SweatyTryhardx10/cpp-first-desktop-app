#pragma once

#include <iostream>
#include <stdint.h>
#include <ctime>
#include "numberdialwidget.h"

class AlarmWidget
{
public:
    AlarmWidget(uint16_t width, uint16_t height)
    {
        size.x = width;
        size.y = height;

        hourDial = new NumberDialWidget(width / 2, height / 2);
        minuteDial = new NumberDialWidget(width / 2, height / 2);

        // Re-establish the scheduled shutdown time
        LoadShutdownTime();
    }

    void Render();
    void SetPosition(uint16_t x, uint16_t y);
    void SetSize(uint16_t w, uint16_t h);

private:
    uint8_t posX;
    uint8_t posY;
    ImVec2 size;
    float vHour = 0;
    float vMinute = 5;
    bool commandIssued = false;

    NumberDialWidget* hourDial;
    NumberDialWidget* minuteDial;

    bool ScheduleShutdownTime(uint32_t seconds);
    void ClearShutdownTime();
    bool SaveShutdownTime(tm shutdownTime);
    void LoadShutdownTime();
};