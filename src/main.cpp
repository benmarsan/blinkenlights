#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <I2S.h>
#include <Adafruit_ZeroFFT.h>

#include "config.h"

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

void drawGraph(float *values[]) {
    for(int x = 0; x < 16; x++) {
        int height = (int) values[x] * 7;
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
    // Array for FFT operations
    int16_t signal[FFT_SIZE];
    float normalized[FFT_SIZE_OUT];

    for(int i = 0; i < FFT_SIZE; i++) {
        signal[i] = I2S.read();
        Serial.println(signal[i]);
    }

    /*ZeroFFT(signal, FFT_SIZE);

    //get the maximum value
    float maxVal = 0;
    //data is only meaningful up to sample rate/2, discard the other half
    for(int i=0; i < FFT_SIZE_OUT; i++) if(signal[i] > maxVal) maxVal = signal[i];

    for(int i=0; i < FFT_SIZE_OUT; i++)
        normalized[i] = (float)signal[i] / maxVal;

    for(int i=0; i < FFT_SIZE_OUT; i++){
        // print the frequency
        //Serial.print(FFT_BIN(i, SAMPLE_RATE, FFT_SIZE));
        //Serial.print(" Hz: ");

        // print the corresponding FFT output
        Serial.print(normalized[i]);

        Serial.print("\t");
    }*/

    Serial.println();
}
