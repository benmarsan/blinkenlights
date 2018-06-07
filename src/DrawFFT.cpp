#include "DrawFFT.h"
#include "config.h"

constexpr int16_t DrawFFT::noise[];
constexpr float DrawFFT::eq[];

DrawFFT::DrawFFT() {
    memset(col , 0, sizeof(col));
}

int DrawFFT::begin() {
    // Setup the LED matrix
    if(!matrix.begin()) {
        Serial.println("LED matrix not found");
        return 0;
    }

    // Clear all frame buffers
    for(int f = 0; f < 7; f++) {
        matrix.setFrame(f);
        matrix.fillScreen(LED_OFF);
    }
    // Reset to first frame
    matrix.setFrame(0);
    matrix.displayFrame(0);

    return 1;
}

void DrawFFT::update(int16_t *spectrum) {
    // Double buffer matrix by drawing to next frame while
    // previous frame is visible on screen
    //matrix.setFrame(drawFrame);

    // Remove noise and apply EQ levels
    for(int k = 0; k < FFT_SIZE_OUT; k++) {
        spectrum[k] = max(spectrum[k] - noise[k], 0);
        spectrum[k] *= eq[k];
    }

    // Downsample spectrum to 15 columns
    for(int x = 0; x < 15; x++) {
        // Average pairs of columns
        // Designed to work with size 64  with 32 output bins. First and last
        // bin are unused.
        int16_t avg = (spectrum[(2*x) + 1] + spectrum[(2*x) + 2]) / 2;

        // Convert raw values to dB/log scale for better display
        col[x][colCount] = 10 * log10(avg);

        // Starting point for finding new min and max levels
        uint16_t minLvl, maxLvl;
        minLvl = maxLvl = col[x][0];

        // Get range of past 10 frames
        for(int i = 1; i < 10; i++) {
            if(col[x][i] < minLvl)
                minLvl = col[x][i];
            else if(col[x][i] > maxLvl)
                maxLvl = col[x][i];
        }

        // If maxLvl and minLvl are too close, then the graph
        // appears 'jumpy', so keep some distance between them
        if((maxLvl - minLvl) < 26)
            maxLvl = minLvl + 26;

        // Exponential moving average
        // https://stackoverflow.com/questions/10990618/calculate-rolling-moving-average-in-c
        minLvlAvg[x] = (minLvl * .2) + (minLvlAvg[x] * .8);
        maxLvlAvg[x] = (maxLvl * .2) + (maxLvlAvg[x] * .8);

        // Create normalized scale based on moving min/max levels
        // (Scale is taller than display)
        int level = 10 * (col[x][colCount] - minLvlAvg[x]) /
                (long)(maxLvlAvg[x] - minLvlAvg[x]);

        // Clip output and convert to byte:
        uint8_t c;

        if(level <= 0L)
            c = 0;
        else if(level > 10)
            c = 10; // Allow dot to go a couple pixels off top
        else
            c = (uint8_t)level;

        // Set new peak if necessary
        if(c > peak[x])
            peak[x] = c;

        // Draw column
        matrix.drawFastVLine(x, 0, 7, LED_OFF);
        if(c == 0) {
            matrix.drawFastVLine(x, 0, 7, LED_OFF);
        } else {
            matrix.drawFastVLine(x, 8, -c, LED_LOW);
        }

        matrix.drawPixel(x, 7 - peak[x], LED_HIGH);
    }

    // Show frame
    //matrix.displayFrame(drawFrame);

    // Every third frame, make the peak pixels drop by 1:
    if(++dotCount >= 3) {
        dotCount = 0;
        for(int x = 0; x < 15; x++) {
            if(peak[x] > 0) peak[x]--;
        }
    }

    // Increment and wrap frame counters
    if(++colCount >= 10) colCount = 0;
    if(++drawFrame > 7) drawFrame = 0;
}
