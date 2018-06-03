#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <Adafruit_ZeroFFT.h>

#include "config.h"
#include "FastADC.h"

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

unsigned int sampling_period_us;
unsigned long microseconds;

// Takes FFT results and draws them to LED matrix
void drawGraph(int16_t values[]) {
    for(int x = 0; x < 16; x++) {
        int height = values[x+1] / 4;

        // Draw bottom of line
        matrix.drawFastVLine(x, 8, -height, BRIGHTNESS_ON);
        // Clear top of line
        matrix.drawFastVLine(x, 0, (7 - height), BRIGHTNESS_OFF);
    }
}

void setup() {
    sampling_period_us = round(1000000*(1.0/SAMPLE_RATE));
    
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

    // Setup ADC for fast reads
    selAnalog(MIC_PIN);
    fastADCsetup();
}

void loop() {
    // signal array stores microphone input data
    int16_t signal[FFT_SIZE];
    int16_t signal_db[FFT_SIZE_OUT];

    for(int i = 0; i < FFT_SIZE; i++) {
        microseconds = micros(); // Overflows after around 70 minutes!

        // Read mic into signal[i]
        signal[i] = anaRead();

#ifdef OUTPUT_RAW
        Serial.println(signal[i]);
#endif

        while(micros() < (microseconds + sampling_period_us)){
            //empty loop
        }
    }

    // Compute FFT
    ZeroFFT(signal, FFT_SIZE);

    for(int i = 0; i < FFT_SIZE_OUT; i++) {
        signal_db[i] = 20 * log10(signal[i]);
    }

    // Draw to matrix
    drawGraph(signal_db);

    // Print FFT data to serial monitor
#ifdef OUTPUT_FFT
    for(int i=0; i < FFT_SIZE_OUT; i++){
        // print the frequency band
#ifdef READABLE_OUTPUT
        Serial.print(FFT_BIN(i, SAMPLE_RATE, FFT_SIZE));
        Serial.print(" Hz: ");
#endif

#ifdef OUTPUT_FFT_REAL
        // print the corresponding FFT output
        Serial.print(signal[i]);
        Serial.print("\t");
#endif
#ifdef OUTPUT_FFT_NORMALIZED
        // print the normalized FFT output
        Serial.print(signal_db[i]);
        Serial.print("\t");
#endif
    }
#endif

    Serial.println();
}
