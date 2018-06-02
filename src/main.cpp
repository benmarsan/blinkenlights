#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <I2S.h>
#include <Adafruit_ZeroFFT.h>

#include "config.h"

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

// Takes FFT results and draws them to LED matrix
void drawGraph(float *values[]) {
    for(int x = 0; x < 16; x++) {
        int height = (int) values[x] * 7;

        // Draw bottom of line
        matrix.drawFastVLine(x, 8, -height, BRIGHTNESS_ON);
        // Clear top of line
        matrix.drawFastVLine(x, 0, (7 - height), BRIGHTNESS_OFF);
    }
}

void setup() {
    // Turn on power button LED
    pinMode(LED_POWER, OUTPUT);
    digitalWrite(LED_POWER, HIGH);

    Serial.begin(115200);

    // Setup the LED matrix
    if (!matrix.begin()) {
        Serial.println("LED matrix not found");
        while (1);
    }
    matrix.fillScreen(BRIGHTNESS_OFF);

    // setup the I2S audio input for SAMPLE_RATE Hz with 32-bits per sample
    if (!I2S.begin(SAMPLE_RATE, 32)) {
        Serial.println("Failed to initialize I2S input");
        while (1);
    }

}

void loop() {
    // signal array stores microphone input data
    int16_t signal[FFT_SIZE];
    // normalized array used to normalize output to 0-1
    float normalized[FFT_SIZE_OUT];

#ifdef OUTPUT_RAW
    for(int i = 0; i < FFT_SIZE; i++) {
        signal[i] = I2S.read();
        Serial.println(signal[i]);
    }
#endif

    // Compute FFT
    ZeroFFT(signal, FFT_SIZE);

    // Normalize values on scale of 0-1
    // get the maximum value
    float maxVal = 0;

    // is only meaningful up to sample rate/2, ignore the other half
    for(int i=0; i < FFT_SIZE_OUT; i++) if(signal[i] > maxVal) maxVal = signal[i];

    for(int i=0; i < FFT_SIZE_OUT; i++)
        normalized[i] = (float)signal[i] / maxVal;

    // Print FFT data to serial monitor
#ifdef OUTPUT_FFT
    for(int i=0; i < FFT_SIZE_OUT; i++){
        // print the frequency
#ifdef READABLE_OUTPUT
        Serial.print(FFT_BIN(i, SAMPLE_RATE, FFT_SIZE));
        Serial.print(" Hz: ");
#endif

        // print the corresponding FFT output
        Serial.print(normalized[i]);
        Serial.print("\t");
    }
#endif

    Serial.println();
}
