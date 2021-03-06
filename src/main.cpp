#include <Arduino.h>
#include "Adafruit_ZeroFFT.h"

#include "config.h"
#include "FastADC.h"
#include "DrawFFT.h"

DrawFFT fftDisplay = DrawFFT();

unsigned long microseconds;
int16_t signal[FFT_SIZE];

void setup() {
    // Turn on power button LED
    pinMode(LED_POWER, OUTPUT);
    digitalWrite(LED_POWER, HIGH);

    Serial.begin(115200);

    // Initialize the display object
    if(!fftDisplay.begin()) {
        Serial.println("DrawFFT begin failed");
        while(1);
    }

    // Increase I2C clock speed to maximum of 400000 Hz to speed up display
    // writes.
    Wire.setClock(400000);

    // Setup ADC for fast reads
    selAnalog(MIC_PIN);
    fastADCsetup();
}

void loop() {
    for(int i = 0; i < FFT_SIZE; i++) {
        microseconds = micros(); // Overflows after around 70 minutes!

        // Read mic into signal[i]
        signal[i] = anaRead() - MIC_DC_OFFSET;

        // Delay for sampling_period_us to read at SAMPLE_RATE
        while(micros() < (microseconds + sampling_period_us));
    }

    // Compute FFT
    ZeroFFT(signal, FFT_SIZE);

    // Draw to matrix
    fftDisplay.update(signal);
}
