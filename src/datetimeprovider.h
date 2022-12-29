#pragma once

#include "idatetimeprovider.h"

class DateTimeProvider : public IDateTimeProvider
{
public:
    unsigned long millis() override;
};

unsigned long DateTimeProvider::millis()
{
    #ifdef ARDUINO
        return ::millis();
    #else
        return 0;
    #endif
}
