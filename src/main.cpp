#include <Arduino.h>

volatile unsigned char *myADMUX = (unsigned char *);
volatile unsigned char *myADCSRA = (unsigned char *);
volatile unsigned char *myADCSRB = (unsigned char *);
volatile unsigned int *myADCDATA = (unsigned int *);

void setup()
{
  // set up the ADC
  adcInit();
  Serial.begin(9600);
}

void loop()
{
  // Get the reading from the ADC
  unsigned int adcReading = adcRead(0);
  // Print it to the serial port
  Serial.println(adcReading);
}

void adcInit()
{
  // Set up the A register
  // Set bit 7 to 1 to enable the ADC
  // clear bit 5 to 0 to disable the ADC trigger mode
  // clear bit 3 to 0 to disable the ADC interrupt
  // clear bits 2-0 to 0 to set prescalar selection to slow reading

  // Setup the B register
  // clear bit 3 to 0 to reset the channel and gain bits
  // clear bits 2-0 to 0 to set free running mode

  // set up the MUX register
  // clear bit 7 to 0 for AVCC analog reference
  // set bit 6 to 1 for AVCC analog reference
  // clear bit 5 to 0 for right adjust result
  // cleat bits 4-0 to 0 to reset the channel and gain bits
}

unsigned int adcRead(unsigned char adcChannelNum)
{
  // clear the channel selection bits (MUX 4:0)
  // On which register?

  // clear the channel selection bits (MUX 5)
  // On which register?

  // set the channel number
  if (adcChannelNum > 7)
  {
    // set the channel selection bits, but remove the most significant bit (bit 3)
    adcChannelNum -= 8;

    // Set MUX bit 5
    // On which register?
  }

  // Set the channel selection bits
  *myADMUX += adcChannelNum;

  // Set bit 6 of ADCSRA to 1 to start a conversion

  // Wait for the conversion to complete
  while ((*myADCSRA & 0x40) != 0)
    // return the result in the ADC data register

    return myADCDATA;
}