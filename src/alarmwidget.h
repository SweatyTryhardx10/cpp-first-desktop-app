#pragma once

#include <iostream>
#include <stdint.h>

class AlarmWidget
{
    public:
        AlarmWidget(uint16_t width, uint16_t height)
        {
            size.x = width;
            size.y = height;
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
};