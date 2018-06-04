#include <Arduino.h>
#include "Adafruit_ZeroFFT.h"

#include "config.h"
#include "FastADC.h"
#include "DrawFFT.h"

DrawFFT fftDisplay = DrawFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

int16_t signal[FFT_SIZE];

// Takes FFT results and draws them to LED matrix
/*void drawGraph(int16_t values[]) {
    for(int x = 0; x < 16; x++) {
        int height = (int) values[x+1];

        // Draw bottom of line
        matrix.drawFastVLine(x, 8, -height, BRIGHTNESS_ON);
        // Clear top of line
        matrix.drawFastVLine(x, 0, (7 - height), BRIGHTNESS_OFF);
    }
}*/

void setup() {
    sampling_period_us = round(1000000*(1.0/SAMPLE_RATE));
    
    // Turn on power button LED
    pinMode(LED_POWER, OUTPUT);
    digitalWrite(LED_POWER, HIGH);

    Serial.begin(115200);

    // Initialize the display object
    if(!fftDisplay.begin()) {
        Serial.println("DrawFFT begin failed");
        while(1);
    }

    // Setup ADC for fast reads
    selAnalog(MIC_PIN);
    fastADCsetup();
}

void loop() {
    for(int i = 0; i < FFT_SIZE; i++) {
        microseconds = micros(); // Overflows after around 70 minutes!

        // Read mic into signal[i]
        signal[i] = anaRead() - MIC_DC_OFFSET;

        while(micros() < (microseconds + sampling_period_us)){
            //empty loop
        }
    }

#ifdef OUTPUT_RAW
    for(int i = 0; i < FFT_SIZE; i++) {
        Serial.print(vReal[i]);
        Serial.print("\t");
    }
    Serial.println();
#endif

    // Compute FFT
    ZeroFFT(signal, FFT_SIZE);

    // Draw to matrix
    //drawGraph(signal);
    fftDisplay.update(signal);

    // Print FFT data to serial monitor
#ifdef OUTPUT_FFT
    for(int i=0; i < FFT_SIZE_OUT; i++){

#ifdef OUTPUT_FFT_REAL
        // print the corresponding FFT output
        Serial.print(signal[i]);
        Serial.print("\t");
#endif
#ifdef OUTPUT_FFT_NORMALIZED
        // print the normalized FFT output
        Serial.print(vReal[i]);
        Serial.print("\t");
#endif
    }

    Serial.println();
#endif
}
