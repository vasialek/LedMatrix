#include "effects/fireworkeffect.h"
#include "effects/life.h"
#include "effects/snake.h"
#include "interfaces/ilogger.h"
#include "models/acolors.h"
#include "effects/baseeffectrunner.h"
#include "effects/scanner.h"
#include "effects/finalcountdowneffect.h"
#include "datetimeprovider.h"
#include "providers/randomprovider.h"

#ifdef ARDUINO
#include <Arduino.h>
#include "loggers/seriallogger.h"
#include <FastLED.h>
#include "loggers/seriallogger.h"
#else
#include <cstdlib>
#include <unistd.h>
#include "loggers/consolelogger.h"
#endif

const int Width = 10;
const int Height = 10;

DateTimeProvider _dateTimeProvider;

#ifdef ARDUINO
ILogger* _logger = new SerialLogger(&_dateTimeProvider);

#define NUM_LEDS 100
CRGB leds[NUM_LEDS];

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2
#else
ILogger* _logger = new ConsoleLogger();
#endif

void Delay(int ms)
{
#ifdef ARDUINO
    delay(ms);
#else
    usleep(ms * 1000);
#endif
}

MatrixHelper _matrixHelper;
RandomProvider _randomProvider;
Scanner _scanner(&_dateTimeProvider, &_matrixHelper, Width, Height);
// FinalCountdownEffect _finalCountdownEffect(&_dateTimeProvider, &_matrixHelper, _logger, Width, Height);
FireworkEffect _fireworkEffect(&_dateTimeProvider, &_matrixHelper, &_randomProvider, _logger, Width, Height);
Life _life(&_dateTimeProvider, &_randomProvider, &_matrixHelper, Width, Height, 60);
Snake _snake(&_dateTimeProvider, &_randomProvider, &_matrixHelper, 9, 0, -1, 1);

// char _logBuffer[256];

int _effectsCount = -1;
int _currentEffectNr = 0;
BaseEffectRunner** _effects = nullptr;
BaseEffectRunner* _currentEffect = nullptr;

void InitializeEffects();

#ifdef ARDUINO

void FillMatrix(MatrixSnapshot* snapshot);
CRGB MapColorToCrgb(unsigned char color);

void setup()
{
    Serial.begin(9600);
    Serial.println("Setup");
    // _logger->Debug("Setup...");
    pinMode(LED_BUILTIN, OUTPUT);
    // FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    for (size_t i = 0; i < 5; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    // FastLED.setBrightness(100);

    
    // _logger->Debug("Initializing effects...");
    InitializeEffects();
    Delay(2000);
    Serial.println("Setup done");
}

void loop()
{
    _logger->Debug("Looping...");
    FastLED.clear();

    auto snapshot = _currentEffect->GetSnapshot();
    FillMatrix(snapshot);

    _logger->Debug("Showing FastLED");
    FastLED.show();

    if (_currentEffect->IsFinished())
    {
        _currentEffect->Reset();
        _currentEffectNr++;
        if (_currentEffectNr >= _effectsCount)
        {
            _currentEffectNr = 0;
        }
        _currentEffect = _effects[_currentEffectNr];
    }

    _currentEffect->Move();
    Delay(50);
}

void FillMatrix(MatrixSnapshot* snapshot)
{
    for (int i = 0; i < snapshot->totalCells; i++)
    {
        leds[i] = MapColorToCrgb(snapshot->cells[i]);
    }
}

CRGB MapColorToCrgb(unsigned char color)
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

#endif

#ifndef ARDUINO
void ClearScreen();
void ShowMatrix(MatrixSnapshot* snapshot);

int main()
{
    InitializeEffects();

    for (size_t i = 0; i < 1000; i++)
    {
        ClearScreen();
        auto snapshot = _currentEffect->GetSnapshot();
        ShowMatrix(snapshot);

        if (_currentEffect->IsFinished())
        {
            _currentEffect->Reset();
            _currentEffectNr++;
            if (_currentEffectNr >= _effectsCount)
            {
                _currentEffectNr = 0;
            }

            // sprintf(buffer, "Current effect #%d", _currentEffectNr);
            // _logger->Info(buffer);
            // Delay(2000);
            // _currentEffectNr = (_currentEffectNr + 1) % _effectCount;
            _currentEffect = _effects[_currentEffectNr];
        }

        _currentEffect->Move();
        Delay(100);
    }

    return 0;
}

char GetColorSymbol(unsigned char color)
{
    switch (color)
    {
    case ACOLOR_RED:
        return 'R';
    case ACOLOR_GREEN:
        return 'G';
    case ACOLOR_BLUE:
        return 'B';
    case ACOLOR_YELLOW:
        return 'Y';
    case ACOLOR_WHITE:
        return 'W';
    case ACOLOR_ORANGE:
        return 'O';
    default:
        return '#';
    }
}

void ShowMatrix(MatrixSnapshot* snapshot)
{
    if (snapshot == nullptr)
    {
        return;
    }
    char buf[Width + 3];
    int index = 0;
    for (int y = 0; y < Height; y++)
    {
        buf[0] = '|';
        for (int x = 0; x < Width; x++)
        {
            index = _matrixHelper.GetMatrixIndex(x, y);
            buf[x + 1] = snapshot->cells[index] == ACOLOR_OFF ? '.' : GetColorSymbol(snapshot->cells[index]);
            // index++;
        }
        buf[Width + 1] = '|';
        buf[Width + 2] = 0;
        _logger->Info(buf);
    }
}

void ClearScreen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}

#endif

void InitializeEffects()
{
    static BaseEffectRunner* registry[] = {
        // &_scanner,
        // &_finalCountdownEffect,
        &_fireworkEffect,
        // &_snake,
        // &_life
    };

    _effects = registry;
    _effectsCount = sizeof(registry) / sizeof(registry[0]);
    _currentEffectNr = 0;
    _currentEffect = _effects[_currentEffectNr];

    if (_currentEffect)
    {
        _currentEffect->Reset();
    }
    Serial.println("Effects initialized");
}

// void setup()
// {
//     Serial.begin(9600);
//     pinMode(LED_BUILTIN, OUTPUT);
// FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
//     for (size_t i = 0; i < 5; i++)
//     {
//         digitalWrite(LED_BUILTIN, HIGH);
//         delay(500);
//         digitalWrite(LED_BUILTIN, LOW);
//         delay(500);
//     }
//     FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
//     FastLED.setBrightness(100);
//     // _ballMover.SetBall(0, 2);
//     _scanner.SetDelayMs(150);
//     _snake.SetDelayMs(180);
//     _life.SetDelayMs(1500);
//     _currentEffect = SwicthNextEffect();
//     // Seed random
//     randomSeed(analogRead(0));
// }

// void loop()
// {
//     FastLED.clear();

//     auto snapshot = _currentEffect->GetSnapshot();
//     // auto snapshot = _ballMover.GetSnapshot();
//     // auto snapshot = _scanner.GetSnapshot();
//     // auto snapshot = _life.GetSnapshot();
//     // auto snapshot = _snake.GetSnapshot();
//     FillMatrix(snapshot);

//     FastLED.show();

//     _currentEffect->Move();
//     if (_currentEffect->IsFinished())
//     {
//         SwicthNextEffect();
//     }

//     // _scanner.Move();
//     // if (_scanner.IsFinished())
//     // {
//     //     auto snapshot = _life.GetSnapshot();
//     //     FillMatrix(snapshot);
//     //     FastLED.show();
//     //     delay(20000);
//     // }

//     // _life.Move();
//     // _snake.Move();
//     // if (_snake.IsFinished())
//     // {
//     //     auto snapshot = _life.GetSnapshot();
//     //     FillMatrix(snapshot);
//     //     FastLED.show();
//     //     delay(20000);
//     //     _snake.Restart();
//     // }

//     delay(50);
// }

// BaseEffectRunner *SwicthNextEffect()
// {
//     /*
//     *   1:  Scanner
//     *   2:  Snake
//     *   3:  Scanner
//     *   4:  Life
//     *   5:  Scanner
//     */
//     _currentEffectNr++;
//     Serial.print("New effect nr: ");
//     Serial.println(_currentEffectNr);
//     switch (_currentEffectNr)
//     {
//     case 1:
//     case 3:
//     case 5:
//         _currentEffect = &_scanner;
//         break;

//     case 2:
//         _currentEffect = &_snake;
//         break;

//     case 4:
//         _currentEffect = &_life;
//         break;

//     default:
//         _currentEffectNr = 0;
//         _currentEffect = &_scanner;
//         break;
//     }

//     return _currentEffect;
// }
