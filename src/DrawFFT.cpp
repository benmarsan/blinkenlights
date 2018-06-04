#include "DrawFFT.h"
#include "config.h"

DrawFFT::DrawFFT() {
    memset(col , 0, sizeof(col));
}

int DrawFFT::begin() {
    // Setup the LED matrix
    if(!matrix.begin()) {
        Serial.println("LED matrix not found");
        return 0;
    }

    return 1;
}

void DrawFFT::update(int16_t *spectrum) {
    uint8_t  i, L, *data, nBins, binNum, weighting, c;
    uint16_t minLvl, maxLvl;
    int level, y, sum;

    uint32_t start = micros();

    // Write to drawFrame while previous frame is visible
    matrix.setFrame(drawFrame);

    // Remove noise and apply EQ levels

    // Downsample spectrum to 15 columns
    for(int x = 0; x < 15; x++) {
        col[x][colCount] = 10 * log10(spectrum[x+1]);

        // Starting point for finding new min and max levels
        minLvl = maxLvl = col[x][0];

        // Get range of past 10 frames
        for(i=1; i<10; i++) {
            if(col[x][i] < minLvl)
                minLvl = col[x][i];
            else if(col[x][i] > maxLvl)
                maxLvl = col[x][i];
        }

        // If maxLvl and minLvl are too close, then the graph
        // appears 'jumpy', so keep some distance between them
        if((maxLvl - minLvl) < 24)
            maxLvl = minLvl + 24;
        
        // Fake rolling average of minLvl and maxLvl
        minLvlAvg[x] = (minLvlAvg[x] * 7 + minLvl) >> 3; // Dampen min/max levels
        maxLvlAvg[x] = (maxLvlAvg[x] * 7 + maxLvl) >> 3; // (fake rolling average)

        // Create normalized scale based on moving min/max levels
        // (Scale is taller than display)
        level = 10L * (col[x][colCount] - minLvlAvg[x]) /
                (long)(maxLvlAvg[x] - minLvlAvg[x]);

        // Clip output and convert to byte:
        if(level < 0L)
            c = 0;
        else if(level > 10)
            c = 10; // Allow dot to go a couple pixels off top
        else
            c = (uint8_t)level;

        Serial.print("x: ");
        Serial.print(x);
        Serial.print(" c: ");
        Serial.println(c);
        
        // Set new peak if necessary
        if(c > peak[x])
            peak[x] = c;

        // Draw column
        if(peak[x] <= 0) { // Empty column
            matrix.drawFastVLine(x, 0, 7, LED_OFF);
        } else if(c < 8) { // Partial column
            matrix.drawFastVLine(x, 0, 7 - c, LED_OFF);
            matrix.drawFastVLine(x, 7 - c, c, LED_LOW);
        }

        // The 'peak' dot color varies, but doesn't necessarily match
        // the three screen regions...yellow has a little extra influence.
        y = 7 - peak[x];
        matrix.drawPixel(x, y, LED_HIGH);
    }

    // Show frame
    matrix.displayFrame(drawFrame);

    // Every third frame, make the peak pixels drop by 1:
    if(++dotCount >= 3) {
        dotCount = 0;
        for(int x = 0; x < 15; x++) {
            if(peak[x] > 0) peak[x]--;
        }
    }

    // Increment and wrap frame counters
    if(++colCount >= 10) colCount = 0;
    if(++drawFrame >= 7) drawFrame = 0;

    uint32_t time = micros() - start;
    Serial.print("FFT time: ");
    Serial.print(time);
    Serial.println(" us");
}