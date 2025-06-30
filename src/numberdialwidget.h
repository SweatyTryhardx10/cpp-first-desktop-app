#pragma once

#include <iostream>
#include <stdint.h>
#include <cmath>

class NumberDialWidget
{
    public:
        NumberDialWidget(uint16_t width, uint16_t height, float min_angle_stop = 1.3f * M_PI, float max_angle_stop = -0.3f * M_PI)
        {
            this->width = width;
            this->height = height;
            this->minAngle = min_angle_stop;
            this->maxAngle = max_angle_stop;
        }
        bool Render(const char* label);
        
    private:
        uint16_t width;
        uint16_t height;
        float minAngle;
        float maxAngle;
        float v;
        
};