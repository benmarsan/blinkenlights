#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

#define MIC_PIN          A0
#define LED_POWER        10

#define BRIGHTNESS_OFF   0x01
#define BRIGHTNESS_ON    0x09

#define SAMPLE_RATE      16000
#define FFT_SIZE         64
#define FFT_SIZE_OUT     (FFT_SIZE / 2)
#define MIC_DC_OFFSET    1.25 / 3.3 * 4096

constexpr unsigned int sampling_period_us = round(1000000*(1.0/SAMPLE_RATE));

#endif
