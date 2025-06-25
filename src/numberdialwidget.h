#pragma once

#include <iostream>
#include <stdint.h>

class NumberDialWidget
{
    public:
        NumberDialWidget(uint16_t width, uint16_t height)
        {
            this->width = width;
            this->height = height;
        }
        void Render();
        
    private:
        uint16_t width;
        uint16_t height;
};