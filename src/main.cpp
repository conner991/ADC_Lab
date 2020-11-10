#include <Arduino.h>

volatile unsigned char *myADCSRA = (unsigned char *)0x7A;
volatile unsigned char *myADCSRB = (unsigned char *)0x7B;
volatile unsigned char *myADMUX = (unsigned char *)0x7C;
volatile unsigned int *myADCDATA = (unsigned int *)0x78;

// Prototypes
void adcInit();
unsigned int adcRead(unsigned char adcChannelNum);

void setup()
{
  // set up the ADC
  adcInit();
  Serial.begin(9600);
}

void loop()
{
  // Get the reading from the ADC
  unsigned int adcReading = adcRead(5);

  // Delay
  delay(250);

  // Print it to the serial port
  Serial.println(adcReading);
}

void adcInit()
{
  // Set up the A register
  // Set bit 7 to 1 to enable the ADC
  *myADCSRA |= 0x80;
  // clear bit 5 to 0 to disable the ADC trigger mode
  *myADCSRA &= 0xDF;
  // clear bit 3 to 0 to disable the ADC interrupt
  *myADCSRA &= 0xF7;
  // clear bits 2-0 to 0 to set prescalar selection to slow reading (Division Factor of 2)
  *myADCSRA &= 0xF8;

  // Setup the B register
  // clear bit 3 to 0 to reset the channel and gain bits
  *myADCSRB &= 0xF7;
  // clear bits 2-0 to 0 to set free running mode
  *myADCSRB &= 0xF8;

  // set up the MUX register
  // clear bit 7 to 0 for AREF, internal Vref turned off
  *myADMUX &= 0x7F;
  // set bit 6 to 1 for AVCC analog reference, external capacitor at AREF pin
  *myADMUX |= 0x40;
  // clear bit 5 to 0 for right adjust result
  *myADMUX &= 0xDF;
  // clear bits 4-0 to 0 to reset the channel and gain bits
  *myADMUX &= 0xE0;
}

unsigned int adcRead(unsigned char adcChannelNum)
{
  // clear the channel selection bits (MUX 4:0)
  *myADMUX &= 0xE0;

  // clear the channel selection bits (MUX 5)
  *myADCSRB &= 0xF7;

  // set the channel number
  if (adcChannelNum > 7)
  {
    // set the channel selection bits, but remove the most significant bit (bit 3)
    adcChannelNum -= 8;

    // Set MUX 5
    *myADCSRB |= 0x08;
  }

  // Set the channel selection bits
  *myADMUX += adcChannelNum;

  // Set bit 6 of ADCSRA to 1 to start a conversion
  *myADCSRA |= 0x40;

  // Wait for the conversion to complete
  while ((*myADCSRA & 0x40) != 0)
    ;

  // return the result in the ADC data register
  return *myADCDATA;
}