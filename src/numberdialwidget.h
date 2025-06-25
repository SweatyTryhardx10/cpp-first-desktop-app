#pragma once

#include <iostream>
#include <tchar.h>

class NumberDialWidget
{
    public:
        NumberDialWidget(uint8_t width, uint8_t height)
        {
            this->width = width;
            this->height = height;
        }
        void Render();
        
    private:
        uint8_t width;
        uint8_t height;
};