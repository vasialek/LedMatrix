#pragma once

#include "../interfaces/idatetimeprovider.h"
#ifdef ARDUINO
#include "Arduino.h"
#else
#include <chrono>
// unsigned long _
#endif

class DateTimeProvider : public IDateTimeProvider
{
    unsigned long _startedAt = 0;

public:
    DateTimeProvider()
    {
        _startedAt = millis();
    }

    unsigned long millis() override;
};

inline unsigned long DateTimeProvider::millis()
{
#ifdef ARDUINO
    return ::millis();
#else
    using namespace std::chrono;
    auto now = system_clock::now().time_since_epoch().count() / 1000000;
    return now - _startedAt;
#endif
}
