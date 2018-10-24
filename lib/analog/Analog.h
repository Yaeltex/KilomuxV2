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

#pragma once

#include "DataTypes.h"

#define NUM_MUX             4
#define NUM_MUX_CHANNELS    16

class Analog{
public:                             // These are methods and variables accesible from Arduino IDE
    Analog();                      // Class constructor
    // Methods
    static int init(void);       // Read analog data from multiplexer          
    static int update(void);       // Read analog data from multiplexer          

    static unsigned int isNoise(unsigned int newValue, unsigned int prevValue, bool direction);  // Method to determine if the reading is noise or a true change    

    inline void setFastRead(bool fast) { fastReadEnabled = fast; return; };
    
    // Mux readings
    unsigned int muxReadings[NUM_MUX][NUM_MUX_CHANNELS];                  // Present readings
    unsigned int muxPrevReadings[NUM_MUX][NUM_MUX_CHANNELS];              // Previous readings

private:
    // Variables
    // Address lines for multiplexer
    const int _S0 = 2;
    const int _S1 = 3;
    const int _S2 = 4;
    const int _S3 = 5;
    // Input signal of multiplexers
    const byte InMuxA = A1;
    const byte InMuxB = A2;
    const byte InMuxC = A3;
    const byte InMuxD = A4;
    // Fast read flag
    bool fastReadEnabled = true;

    // Methods
    // FAST ADC
    static uint32_t analogReadFast(byte ADCpin);
    static uint32_t selectAnalogPin(uint32_t ulPin);
    static uint32_t fastADCsetup();
}