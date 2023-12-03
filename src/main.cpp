// temporary for testing
#include <cstdlib>
#include <chrono>
#include <thread>
#ifndef ARDUINO
    #include<unistd.h>
#endif
void ClearScreen() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system ("clear");
#endif
}
void Delay(int ms) {
#ifdef ARDUINO
    delay(ms * 1000);
#else
    usleep(ms * 1000);
#endif
}

// #include <FastLED.h>
#include "ilogger.h"
#include "seriallogger.h"
#include "consolelogger.h"
#include "acolors.h"
#include "baseeffectrunner.h"
#include "mazegenerator.h"
// #include "scanner.h"
// #include "ballmover.h"
// #include "life.h"
// #include "snake.h"
#include "datetimeprovider.h"
// #include "randomprovider.h"

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

// MatrixHelper _matrixHelper;
DateTimeProvider _dateTimeProvider;
// ILogger *logger = new ConsoleLogger();
ILogger *logger = new SerialLogger(&_dateTimeProvider);
RandomProvider _randomProvider;
// BallMover _ballMover(&_matrixHelper, Width, Height);
// Scanner _scanner(&_dateTimeProvider, &_matrixHelper, Width, Height);
// Life _life(&_dateTimeProvider, &_randomProvider, &_matrixHelper, Width, Height, 60);
// Snake _snake(&_dateTimeProvider, &_randomProvider, &_matrixHelper, 9, 0, -1, 1);
MazeBuilder mazeBuilder(&_randomProvider, logger, Width, Height);
MazeGenerator _mazeGenerator(&mazeBuilder, logger, Width, Height);
BaseEffectRunner *_currentEffect = nullptr;
int _currentEffectNr = 0;

// void FillMatrix(MatrixSnapshot *snapshot);
// CRGB MapColorToCrgb(unsigned char color);
// BaseEffectRunner *SwicthNextEffect();
void ShowMatrix(MatrixSnapshot *snapshot);

int main() {
    logger->Info("Working?");
    logger->Debug("Working as debug?");

    _currentEffect = &_mazeGenerator;

    for (size_t i = 0; i < 100; i++)
    {
        ClearScreen();
        auto snapshot = _currentEffect->GetSnapshot();
        ShowMatrix(snapshot);

        if (_currentEffect->IsFinished()) {
            return 0;
        }

        _currentEffect->Move();
        Delay(3000);
    }
    

    return 0;
}

void ShowMatrix(MatrixSnapshot *snapshot) {
    char buf[Width + 3];
    int index = 0;
    for (int i = 0; i < Height; i++)
    {
        buf[0] = '|';
        for (int x = 0; x < Width; x++)
        {
            buf[x + 1] = snapshot->cells[index] == ACOLOR_OFF ? ' ' : '#';
            index++;
        }
        buf[Width] = '|';
        buf[Width + 1] = 0;
        logger->Info(buf);
    }
}


// void setup()
// {
//     Serial.begin(9600);
//     pinMode(LED_BUILTIN, OUTPUT);

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
