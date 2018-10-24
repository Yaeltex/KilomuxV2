/*
    Yaeltex MIDI controller
    Author: Franco Grassano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "Analog.h"

/*
  Method:         Analog
  Description:    Class constructor. Sets everything for a Kilomux Shield to work properly.
  Parameters:     void
  Returns:        void
*/
Analog::Analog(){
    
}

void Analog::init(){
     // Set output pins for multiplexers
    pinMode(_S0, OUTPUT);
    pinMode(_S1, OUTPUT);
    pinMode(_S2, OUTPUT);
    pinMode(_S3, OUTPUT);

    fastReadEnabled = true;
    fastADCsetup();
    
    // Set every reading to 0
    for (int mux = 0; mux < NUM_MUX; mux++) {
      for (int chan = 0; chan < NUM_MUX_CHANNELS; chan++) {
        muxReadings[mux][chan] = 0;
        muxPrevReadings[mux][chan] = 0;
      }
    }
}

int Analog::update(void){

}

//##############################################################################
// Fast analogue read analogReadFast()  
// This is a stripped down version of analogRead() where the set-up commands
// are executed during setup()
// ulPin is the analog input pin number to be read.
//  Mk. 2 - has some more bits removed for speed up
//##############################################################################
uint32_t Analog::analogReadFast(byte ADCpin) {
  selAnalog(ADCpin);
  ADC->INTFLAG.bit.RESRDY = 1;              // Data ready flag cleared
  ADCsync();
  ADC->SWTRIG.bit.START = 1;                // Start ADC conversion
  while ( ADC->INTFLAG.bit.RESRDY == 0 );   // Wait till conversion done
  ADCsync();
  uint32_t valueRead = ADC->RESULT.reg;     // read the result
  ADCsync();
  ADC->SWTRIG.reg = 0x01;                    //  and flush for good measure
  return valueRead;
}
//##############################################################################

//###################################################################################
// ADC set-up  here
//
//###################################################################################
#define PRESCALER_4 0x000
#define PRESCALER_8 0x100
#define PRESCALER_16 0x200
#define PRESCALER_32 0x300
#define PRESCALER_64 0x400
#define PRESCALER_128 0x500
#define PRESCALER_256 0x600
#define PRESCALER_512 0x700

#define RESOL_12BIT 0x00
#define RESOL_10BIT 0x20
#define RESOL_8BIT  0x30
uint32_t Analog::fastADCsetup() {
  //Input control register
  ADCsync();
  ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain select as 1X
  //Set ADC reference source
  ADCsync();
  ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC0_Val; //  2.2297 V Supply VDDANA
  // Set sample length and averaging
  ADCsync();
  ADC->AVGCTRL.reg = 0x00 ;       //Single conversion no averaging
  ADCsync();
  ADC->SAMPCTRL.reg = 0x00;       //Minimal sample length is 1/2 CLK_ADC cycle
  //Control B register
  ADCsync();
  ADC->CTRLB.reg =  PRESCALER_32 | RESOL_10BIT; 
  // Enable ADC in control B register
  ADCsync();
  ADC->CTRLA.bit.ENABLE = 0x01;  
  
 //Enable interrupts
  // ADC->INTENSET.reg |= ADC_INTENSET_RESRDY; // enable Result Ready ADC interrupts
  // ADCsync();

   // NVIC_EnableIRQ(ADC_IRQn); // enable ADC interrupts
   // NVIC_SetPriority(ADC_IRQn, 1); //set priority of the interrupt - higher number -> lower priority
}

//###################################################################################
// ADC select here
//
//###################################################################################

uint32_t Analog::selectAnalogPin(uint32_t ulPin){      // Selects the analog input channel in INPCTRL
  ADCsync();
  ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[ulPin].ulADCChannelNumber; // Selection for the positive ADC input
}

static void ADCsync() {
  while (ADC->STATUS.bit.SYNCBUSY == 1); //Just wait till the ADC is free
}
