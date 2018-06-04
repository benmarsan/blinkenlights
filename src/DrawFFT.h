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

    static constexpr int16_t noise[64] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };
    /*
    static const uint8_t
        noise[64],      // This is low-level noise that's subtracted from each FFT output column:
        eq[64],         // These are scaling quotients for each FFT output column, sort of a
                        // graphic EQ in reverse.  Most music is pretty heavy at the bass end.
        // When filtering down to 8 columns, these tables contain indexes
        // and weightings of the FFT spectrum output values to use.  Not all
        // buckets are used -- the bottom-most and several at the top are
        // either noisy or out of range or generally not good for a graph.
        col0data[],
        col1data[],
        col2data[],
        col3data[],
        col4data[],
        col5data[],
        col6data[],
        col7data[];
    // And then this points to the start of the data for each of the columns:
    const uint8_t* colData[15];*/

  public:
    DrawFFT();
    int begin();
    void update(int16_t *spectrum);
};

#endif