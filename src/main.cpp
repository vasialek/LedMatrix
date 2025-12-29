#include "effects/fireworkeffect.h"
#include "effects/snake.h"
#ifdef ARDUINO
#include "loggers/seriallogger.h"
#else
#include "loggers/consolelogger.h"
#endif

#include "interfaces/ilogger.h"
#include "datetimeprovider.h"

// ILogger *logger;
DateTimeProvider _dateTimeProvider;

#ifdef ARDUINO
    ILogger *logger = new SerialLogger(&_dateTimeProvider);
#else
    ILogger *_logger = new ConsoleLogger();
#endif

#include "interfaces/ilogger.h"
#ifdef ARDUINO
    #include <Arduino.h>
    #include "loggers/seriallogger.h"
    #include <FastLED.h>
#else
    #include <cstdlib>
    #include <unistd.h>
    #include "loggers/consolelogger.h"
#endif
#include "interfaces/ilogger.h"
// #include "ilogger.h"
// #include "seriallogger.h"
// #include "loggers/consolelogger.h"
#include "models/acolors.h"
#include "effects/baseeffectrunner.h"
// #include "mazegenerator.h"
#include "effects/scanner.h"
#include "effects/finalcountdowneffect.h"
#include "ballmover.h"
// #include "life.h"
// #include "snake.h"
#include "datetimeprovider.h"
#include "providers/randomprovider.h"

void ClearScreen() {
#ifdef ARDUINO
#elif defined(WINDOWS)
    std::system("cls");
#else
    std::system("clear");
#endif
}
void Delay(int ms) {
#ifdef ARDUINO
    delay(ms * 1000);
#else
    usleep(ms * 1000);
#endif
}

const int Width = 10;
const int Height = 10;

// How many leds in your strip?
#define NUM_LEDS 100

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2

// Define the array of leds
// CRGB leds[NUM_LEDS];

MatrixHelper _matrixHelper;
RandomProvider _randomProvider;
// BallMover _ballMover(&_matrixHelper, Width, Height);
Scanner _scanner(&_dateTimeProvider, &_matrixHelper, Width, Height);
FinalCountdownEffect _finalCountdownEffect(&_dateTimeProvider, &_matrixHelper, _logger, Width, Height);
FireworkEffect _fireworkEffect(&_dateTimeProvider, &_matrixHelper, _logger, Width, Height);
// Life _life(&_dateTimeProvider, &_randomProvider, &_matrixHelper, Width, Height, 60);
// Snake _snake(&_dateTimeProvider, &_randomProvider, &_matrixHelper, 9, 0, -1, 1);
// MazeBuilder mazeBuilder(&_randomProvider, logger, Width, Height);
// MazeBuilder mazeBuilder(&_randomProvider, logger, 5, 5);
// MazeGenerator _mazeGenerator(&mazeBuilder, logger, Width, Height);
const int _effectCount = 3;
BaseEffectRunner* _effects[_effectCount];
BaseEffectRunner* _currentEffect = nullptr;
int _currentEffectNr = 0;

// void FillMatrix(MatrixSnapshot *snapshot);
// CRGB MapColorToCrgb(unsigned char color);
// BaseEffectRunner *SwicthNextEffect();
void ShowMatrix(MatrixSnapshot *snapshot);

int main() {

    // _currentEffect = &_fireworkEffect;
    // _currentEffect = &_finalCountdownEffect;
    // _currentEffect = &_scanner;
    // _currentEffect = &_snake;
    // char buffer[128];
    // sprintf(buffer, "Before: %lu", _dateTimeProvider.millis());
    // _logger->Info(buffer);
    // Delay(2000);
    // sprintf(buffer, "After:  %lu", _dateTimeProvider.millis());
    // _logger->Info(buffer);

    _effects[0] = &_scanner;
    _effects[1] = &_finalCountdownEffect;
    _effects[2] = &_fireworkEffect;

    _currentEffectNr = 0;
    _currentEffect = _effects[_currentEffectNr];

    // for (size_t i = 0; i < 100 && !_currentEffect->IsFinished(); i++)
    for (size_t i = 0; i < 1000; i++)
    {
        ClearScreen();
        auto snapshot = _currentEffect->GetSnapshot();
        ShowMatrix(snapshot);

        if (_currentEffect->IsFinished())
        {
            _currentEffectNr = (_currentEffectNr + 1) % _effectCount;
            _currentEffect = _effects[_currentEffectNr];
        }

        _currentEffect->Move();
        Delay(100);
    }

    // MatrixSnapshot snapshot;
    // snapshot.totalCells = 100;
    // snapshot.cells = new uint8_t[snapshot.totalCells];
    // for (size_t i = 0; i < snapshot.totalCells; i++)
    // {
    //     snapshot.cells[i] = ACOLOR_OFF;
    // }
    // snapshot.cells[_matrixHelper.GetMatrixIndex(0, 0)] = ACOLOR_RED;
    // snapshot.cells[_matrixHelper.GetMatrixIndex(1, 1)] = ACOLOR_RED;
    // snapshot.cells[_matrixHelper.GetMatrixIndex(2, 2)] = ACOLOR_RED;
    // snapshot.cells[_matrixHelper.GetMatrixIndex(3, 3)] = ACOLOR_RED;
    // snapshot.cells[_matrixHelper.GetMatrixIndex(4, 4)] = ACOLOR_RED;
    // ShowMatrix(&snapshot);

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
    for (int i = 0; i < Height; i++)
    {
        buf[0] = '|';
        for (int x = 0; x < Width; x++)
        {
            buf[x + 1] = snapshot->cells[index] == ACOLOR_OFF ? '.' : GetColorSymbol(snapshot->cells[index]);
            index++;
        }
        buf[Width + 1] = '|';
        buf[Width + 2] = 0;
        _logger->Info(buf);
    }
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

// void FillMatrix(MatrixSnapshot *snapshot)
// {
//     for (int i = 0; i < snapshot->totalCells; i++)
//     {
//         leds[i] = MapColorToCrgb(snapshot->cells[i]);
//     }
// }

// CRGB MapColorToCrgb(unsigned char color)
// {
//     switch (color)
//     {
//     case ACOLOR_OFF:
//         return CRGB::Black;
//     case ACOLOR_BLUE:
//         return CRGB::Blue;
//     case ACOLOR_YELLOW:
//         return CRGB::Yellow;
//     case ACOLOR_RED:
//         return CRGB::Red;
//     case ACOLOR_CYAN:
//         return CRGB::Cyan;
//     case ACOLOR_PURPLE:
//         return CRGB::Purple;
//     case ACOLOR_ORANGE:
//         return CRGB::Orange;
//     case ACOLOR_PINK:
//         return CRGB::DeepPink;
//     case ACOLOR_WHITE:
//         return CRGB::White;
//     default:
//         return CRGB::Green;
//     }
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
