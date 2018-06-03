/*
Fast 13 µs conversion time ADC read routines for Arduino M0 Pro.
by H. J. Whitlow 5 September 2015

There are three routines: 
selAnalog(n):      which selects the analog input channel
fastADCsetup(n):   must be called by setup()
anaRead();         which reads the data. 
Here "n" refers to the analog input pin

IMPORTANT: The Arduino M0 Pro must be powered by an external 
power source as the USB supply is not reliable for fast ADC
operation.
*/

// This is an C/C++ code to insert repetitive code sections in-line pre-compilation
// Wait for synchronization of registers between the clock domains
// ADC
static __inline__ void ADCsync() __attribute__((always_inline, unused));
static void ADCsync() {
    while (ADC->STATUS.bit.SYNCBUSY == 1);
}

//###################################################################################
// ADC select here
//
//###################################################################################

uint32_t selAnalog(uint32_t ulPin) {
    // Selects the analog input channel in INPCTRL
    ADCsync();
    ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[ulPin].ulADCChannelNumber; // Selection for the positive ADC input
}

//###################################################################################
// ADC set-up  here
//
//###################################################################################
uint32_t fastADCsetup() {
    //Input control register
    ADCsync();
    ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val; // Gain select as 1X
    //Set ADC reference source
    ADCsync();
    ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC0_Val; //  2.2297 V Supply VDDANA
    // Set sample length and averaging
    ADCsync();
    ADC->AVGCTRL.reg = 0x00; //Single conversion no averaging
    ADCsync();
    ADC->SAMPCTRL.reg = 0x00; //Minimal sample length is 1/2 CLK_ADC cycle
    //Control B register
    ADCsync();
    ADC->CTRLB.reg = 0x400; // Prescale 64, 12 bit resolution, singel conversion
    // Enable ADC in control B register
    ADCsync();
    ADC->CTRLA.bit.ENABLE = 0x01;
}

//##############################################################################
// Fast analogue read anaRead()
// This is a stripped down version of analogRead() where the set-up commands
// are executed during setup()
// ulPin is the analog input pin number to be read.
//  Mk. 2 - has some more bits removed for speed up
///##############################################################################
uint32_t anaRead() {
    ADC->INTFLAG.bit.RESRDY = 1; // Data ready flag cleared
    ADCsync();
    ADC->SWTRIG.bit.START = 1; // Start ADC conversion
    while (ADC->INTFLAG.bit.RESRDY == 0); // Wait till conversion done
    ADCsync();
    uint32_t valueRead = ADC->RESULT.reg; // read the result
    ADCsync();
    ADC->SWTRIG.reg = 0x01; //  and flush for good measure
    return valueRead;
}