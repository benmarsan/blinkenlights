//#define OUTPUT_RAW
//#define OUTPUT_FFT
//#define OUTPUT_FFT_REAL
//#define OUTPUT_FFT_NORMALIZED

#define MIC_PIN A0
#define LED_POWER 10

#define BRIGHTNESS_OFF 0x01
#define BRIGHTNESS_ON  0x09

#define SAMPLE_RATE      16000
#define FFT_SIZE 64
#define FFT_SIZE_OUT (FFT_SIZE / 2)
#define MIC_DC_OFFSET 1.25 / 3.3 * 4096
