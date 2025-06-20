#pragma once

#include <iostream>
#include <tchar.h>

class AlarmWidget
{
    public:
        AlarmWidget(uint8_t width, uint8_t height)
        {
            this->width = width; 
            this->height = height;
        }
        
        void Render();
        void SetStartTime();
    
    private:
        uint8_t width;
        uint8_t height;
        float v_rad;
        bool commandIssued = false;
};