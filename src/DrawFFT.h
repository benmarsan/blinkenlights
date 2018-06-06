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
    int16_t minLvlAvg[15] = {32767};    // Dynamic adjustment of high and low
    int16_t maxLvlAvg[15] = {0};        //   levels of graph
    int16_t colDiv[15] = {0};           // Used to filter FFT to 15 columns

    static constexpr int16_t noise[32] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };

  public:
    DrawFFT();
    int begin();
    void update(int16_t *spectrum);
};

#endif