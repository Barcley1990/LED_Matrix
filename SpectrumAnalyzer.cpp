#include <Arduino.h>
#include "SpectrumAnalyzer.h"


void adc_Setup()
{
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
}

void fft()
{


}