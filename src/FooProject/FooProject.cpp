#include <Arduino.h>
#include "FooLib.h"

FooClass FooObject;

void setup() {

	pinMode(LED_BUILTIN, OUTPUT);
	SerialUSB.begin(115200);
	delay(1000);

}

void loop() {

	SerialUSB.println("Hello world");
	FooObject.firstFooMethod();
	delay(1000);
	FooObject.secondFooMethod();
	delay(1000);

	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	  delay(1000);                       // wait for a second
	  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	  delay(1000);  

}

