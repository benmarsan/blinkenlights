#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "arduinoFFT.h"

#include "config.h"
#include "FastADC.h"

Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[FFT_SIZE];
double vImag[FFT_SIZE];

// Takes FFT results and draws them to LED matrix
void drawGraph(double values[]) {
    for(int x = 0; x < 16; x++) {
        int height = (int) values[x+1];

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
    int16_t signal_db[FFT_SIZE_OUT];

    for(int i = 0; i < FFT_SIZE; i++) {
        microseconds = micros(); // Overflows after around 70 minutes!

        // Read mic into signal[i]
        vReal[i] = anaRead() - MIC_DC_OFFSET;
        vImag[i] = 0;

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
    FFT.Windowing(vReal, FFT_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
    FFT.Compute(vReal, vImag, FFT_SIZE, FFT_FORWARD); /* Compute FFT */
    FFT.ComplexToMagnitude(vReal, vImag, FFT_SIZE); /* Compute magnitudes */

    for(int i = 0; i < FFT_SIZE_OUT; i++) {
        //vReal[i] = 1 * log10(vReal[i]);
        vReal[i] = sqrt(vReal[i]) / 10;
    }

    // Draw to matrix
    drawGraph(vReal);

    // Print FFT data to serial monitor
#ifdef OUTPUT_FFT
    for(int i=0; i < FFT_SIZE_OUT; i++){
        // print the frequency band

#ifdef OUTPUT_FFT_REAL
        // print the corresponding FFT output
        Serial.print(vReal[i]);
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
