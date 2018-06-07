#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

#ifndef DRAW_FFT_H
#define DRAW_FFT_H

class DrawFFT
{
  private:
    Adafruit_IS31FL3731_Wing matrix;

    uint8_t peak[15] = {0},     // Peak level of each column for falling dots
        dotCount = 0,           // Frame counter for delaying falling dots
        colCount = 0,           // Frame counter for storing past column data
        drawFrame = 1;          // Frame counter for double bufferred drawing

    uint8_t LED_OFF = 0,
            LED_LOW = 8,
            LED_MID = 16,
            LED_HIGH = 64,
            LED_ON = 255;

    uint8_t col[15][10];                // Column levels for past 10 frames
    int16_t minLvlAvg[15] = {0};    // Dynamic adjustment of high and low
    int16_t maxLvlAvg[15] = {32767};        //   levels of graph (probably only sets first item?)
    int16_t colDiv[15] = {0};           // Used to filter FFT to 15 columns

    // Noise constants to subtract from FFT output
    static constexpr int16_t noise[32] = {
            190, 105, 8, 8, 5, 5, 5, 5, // 0-7
            5, 5, 5, 5, 5, 5, 5, 5, // 8-15
            3, 3, 3, 2, 2, 2, 2, 2, // 16-23
            2, 2, 2, 2, 2, 2, 2, 2  // 24-32
        };

    // FFT outputs are multiplied by EQ constants to change weight of certain
    // bins.
    static constexpr float eq[32] = {
            1, 1, 1, 1, 1, 1, 1, 1, // 0-7
            1, 1, 1, 1, 1, 1, 1, 1, // 8-15
            1, 1, 1, 1, 1, 1, 1, 1, // 16-23
            1, 1, 1, 1, 1, 1, 1, 1,  // 24-32
        };

  public:
    DrawFFT();
    int begin();
    void update(int16_t *spectrum);
};

#endif
