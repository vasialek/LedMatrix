#include "effects/fireworkeffect.h"
#include "effects/life.h"
#include "effects/snake.h"
#include "interfaces/ilogger.h"
#include "effects/baseeffectrunner.h"
#include "effects/scanner.h"
#include "effects/finalcountdowneffect.h"
#include "effects/randompoint.h"
#include "providers/datetimeprovider.h"
#include "helpers/delayhelper.h"
#include "providers/randomprovider.h"
#include "helpers/matrixhelpernative.h"

#ifdef ARDUINO
#include <Arduino.h>
#include "loggers/seriallogger.h"
#include "helpers/colorhelper.h"
#include <FastLED.h>
#else
#include <cstdlib>
#include "loggers/consolelogger.h"
#endif

const int Width = 10;
const int Height = 10;
const int NumberOfLeds = 100;
const int LedMatrixDataPin = 2;

DateTimeProvider dateTimeProvider;
RandomProvider randomProvider;
MatrixHelper matrixHelper;

#ifdef ARDUINO

ILogger* logger = new SerialLogger(&dateTimeProvider);
CRGB leds[NumberOfLeds];

#else

ILogger* logger = new ConsoleLogger();
MatrixHelperNative* matrixHelperNative = new MatrixHelperNative(&matrixHelper, logger, Width, Height);

#endif

RandomPoint randomPoint(&dateTimeProvider, &randomProvider, Width, Height);
Scanner scanner(&dateTimeProvider, &matrixHelper, Width, Height);
FinalCountdownEffect finalCountdownEffect(&dateTimeProvider, &matrixHelper, logger, Width, Height);
FireworkEffect fireworkEffect(&dateTimeProvider, &matrixHelper, &randomProvider, logger, Width, Height);
// Life life(&dateTimeProvider, &randomProvider, &matrixHelper, Width, Height, 60);
Snake snake(&dateTimeProvider, &randomProvider, &matrixHelper, 9, 1, -1, -1);
// Snake snake(&dateTimeProvider, &randomProvider, &matrixHelper, 9, 0, -1, 1);

int effectsCount = -1;
int currentEffectNr = 0;
BaseEffectRunner** effects = nullptr;
BaseEffectRunner* currentEffect = nullptr;

void InitializeEffects();
void DoAnimation();
void ClearMatrix();
void ShowMatrix(MatrixSnapshot* snapshot);

#ifdef ARDUINO

void setup()
{
    Serial.begin(9600);
    Serial.println("Setup");
    pinMode(LED_BUILTIN, OUTPUT);

    for (size_t i = 0; i < 5; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }

    FastLED.addLeds<WS2812B, LedMatrixDataPin, GRB>(leds, NumberOfLeds);
    FastLED.setBrightness(50);

    InitializeEffects();

    FastLED.clear();
    FastLED.show();

    DelayHelper::Delay(2000);
    Serial.println("Setup done");
}

void loop()
{
    DoAnimation();
}

#endif

#ifndef ARDUINO

int main()
{
    InitializeEffects();

    while (true)
    {
        DoAnimation();
    }
}

#endif

void InitializeEffects()
{
    static BaseEffectRunner* registry[] = {
        // &randomPoint,
        // &scanner,
        &finalCountdownEffect,
        &fireworkEffect,
        // &scanner,
        // &snake,
        // &life
    };

    effects = registry;
    effectsCount = sizeof(registry) / sizeof(registry[0]);
    currentEffectNr = 0;
    currentEffect = effects[currentEffectNr];

    if (currentEffect)
    {
        currentEffect->Reset();
    }
}

void ClearMatrix()
{
#ifdef ARDUINO
    FastLED.clear();
#elif WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ShowMatrix(MatrixSnapshot* snapshot)
{
#ifdef ARDUINO
    for (int i = 0; i < snapshot->totalCells; i++)
    {
        leds[i] = ColorHelper::MapColorToCrgb(snapshot->cells[i]);
    }

    FastLED.show();
#else
    matrixHelperNative->ShowMatrix(snapshot);
#endif
}

void DoAnimation()
{
    // logger->Debug("Looping...");
    ClearMatrix();

    auto snapshot = currentEffect->GetSnapshot();
    ShowMatrix(snapshot);

    if (currentEffect->IsFinished())
    {
        currentEffect->Reset();
        currentEffectNr++;
        if (currentEffectNr >= effectsCount)
        {
            currentEffectNr = 0;
        }
        // sprintf(logger->buffer, "Effect: %d", currentEffectNr);
        // logger->Debug(logger->buffer);
        // DelayHelper::Delay(5000);
        // Serial.println(buf);
        currentEffect = effects[currentEffectNr];
    }

    currentEffect->Move();
    DelayHelper::Delay(50);
}
