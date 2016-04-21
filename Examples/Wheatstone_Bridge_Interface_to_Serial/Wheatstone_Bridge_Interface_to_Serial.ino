/* Wheatstone Bridge Interface - Library */

/*
	This library was created by Sébastien Parent-Charette for RobotShop.
	It is meant to be used with the RB-Onl-38 from RobotShop.
	This product is available here: http://www.robotshop.com/en/strain-gauge-load-cell-amplifier-shield-2ch.html
	This library may work with other WheatStone bridge interface boards that use an analog pin for input.
	
	Changes history:
	2016-04-21
	v1.10-08
	Added reading and display of both load cells to the basic example.
	
	2015-10-08
	v1.0
	First release of the library. Basic functionality is available.
*/

#include <WheatstoneBridge.h>

WheatstoneBridge wsb_strain1(A0, 365, 565, 0, 1000);
WheatstoneBridge wsb_strain2(A1, 365, 565, 0, 1000);

void setup()
{
  Serial.begin(9600);
  Serial.println("< Wheatstone Bridge Interface to Serial >");
  Serial.println("");
}

int val1;
int valRaw1;
int val2;
int valRaw2;

void loop()
{
  // Read strain 1
  val1 = wsb_strain1.measureForce();
  valRaw1 = wsb_strain1.getLastForceRawADC();
  Serial.println(">> Strain 1 << ");
  Serial.print("\tRaw ADC value: ");
  Serial.println(valRaw1, DEC);
  Serial.print("\tCalculated force: ");
  Serial.println(val1, DEC);
  delay(100);
  
  // Read strain 2
  val2 = wsb_strain2.measureForce();
  valRaw2 = wsb_strain2.getLastForceRawADC();
  Serial.println(">> Strain 2 << ");
  Serial.print("\tRaw ADC value: ");
  Serial.println(valRaw2, DEC);
  Serial.print("\tCalculated force: ");
  Serial.println(val2, DEC);
  Serial.println("");
  
  // Delay for readability
  delay(1000);
}

/* Wheatstone Bridge Interface - Library */