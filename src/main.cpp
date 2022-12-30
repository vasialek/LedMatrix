#include <FastLED.h>
#include "acolors.h"
#include "baseeffectrunner.h"
#include "scanner.h"
// #include "ballmover.h"
#include "life.h"
#include "snake.h"
#include "datetimeprovider.h"
#include "randomprovider.h"

// How many leds in your strip?
#define NUM_LEDS 100

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];

MatrixHelper _matrixHelper;
DateTimeProvider dateTimeProvider;
RandomProvider randomProvider;
// BallMover _ballMover(&_matrixHelper, 10, 10);
// Scanner _scanner(&dateTimeProvider, &_matrixHelper, 10, 10);
Life _life(&dateTimeProvider, &randomProvider, &_matrixHelper, 10, 10, 60);
Snake _snake(&dateTimeProvider, &randomProvider, &_matrixHelper, 9, 0, -1, 1);
// BaseEffectRunner _snake()

void FillMatrix(MatrixSnapshot *snapshot);
CRGB MapColorToCrgb(unsigned char color);

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    for (size_t i = 0; i < 5; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }
    

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(100);
    // _ballMover.SetBall(0, 2);

    // _scanner.SetDelayMs(150);
    _snake.SetDelayMs(180);
    // _life.SetDelayMs(1500);

    // Seed random
    randomSeed(analogRead(0));
}

void loop()
{
    FastLED.clear();

    // auto snapshot = _ballMover.GetSnapshot();
    // auto snapshot = _scanner.GetSnapshot();
    // auto snapshot = _life.GetSnapshot();
    auto snapshot = _snake.GetSnapshot();
    FillMatrix(snapshot);

    FastLED.show();

    // _ballMover.Move();
    // _scanner.Move();
    // _life.Move();
    _snake.Move();
    delay(50);
}

void FillMatrix(MatrixSnapshot *snapshot)
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
    default:
        return CRGB::Green;
    }
}
