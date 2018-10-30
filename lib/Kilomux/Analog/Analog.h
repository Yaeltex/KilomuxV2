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
    static void init();       // Read analog data from multiplexer          
    static void update();       // Read analog data from multiplexer          

    static unsigned int isNoise(unsigned int newValue, unsigned int prevValue, bool direction);  // Method to determine if the reading is noise or a true change    

    static void setFastRead(bool fast);

private:

    // Methods
    // FAST ADC
    static uint32_t analogReadFast(byte ADCpin);
    static uint32_t selectAnalogPin(uint32_t ulPin);
    static uint32_t fastADCsetup();
};

extern Analog analog;