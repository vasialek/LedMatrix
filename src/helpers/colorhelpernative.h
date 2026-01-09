#pragma once

#ifndef ARDUINO

#include "../models/acolors.h"

class ColorHelperNative
{
public:
    static char GetColorSymbol(unsigned char color)
    {
        switch (color)
        {
        case ACOLOR_OFF:
            return '.';
        case ACOLOR_RED:
            return 'R';
        case ACOLOR_GREEN:
            return 'G';
        case ACOLOR_BLUE:
            return 'B';
        case ACOLOR_YELLOW:
            return 'Y';
        case ACOLOR_CYAN:
            return 'C';
        case ACOLOR_PURPLE:
            return 'U';
        case ACOLOR_ORANGE:
            return 'O';
        case ACOLOR_PINK:
            return 'P';
        case ACOLOR_WHITE:
            return 'W';
        default:
            return '#';
        }
    }
};

#endif
