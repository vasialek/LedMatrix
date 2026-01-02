#pragma once

#ifdef ARDUINO

#include "FastLED.h"

class ColorHelper
{
public:
    static CRGB MapColorToCrgb(unsigned char color)
    {
        switch (color)
        {
        case ACOLOR_OFF:
            return CRGB::Black;
        case ACOLOR_BLUE:
            return CRGB::Blue;
        case ACOLOR_YELLOW:
            return CRGB::Yellow;
        case ACOLOR_RED:
            return CRGB::Red;
        case ACOLOR_CYAN:
            return CRGB::Cyan;
        case ACOLOR_PURPLE:
            return CRGB::Purple;
        case ACOLOR_ORANGE:
            return CRGB::Orange;
        case ACOLOR_PINK:
            return CRGB::DeepPink;
        case ACOLOR_WHITE:
            return CRGB::White;
        default:
            return CRGB::Green;
        }
    }
};

#endif
