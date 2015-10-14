/* Wheatstone Bridge Interface - Library */

/*
	This library was created by Sébastien Parent-Charette for RobotShop.
	It is meant to be used with the RB-Onl-38 from RobotShop.
	This product is available here: http://www.robotshop.com/en/strain-gauge-load-cell-amplifier-shield-2ch.html
	This library may work with other WheatStone bridge interface boards that use an analog pin for input.
	
	Changes history:
	2015-10-08
	v1.0
	First release of the library. Basic functionality is available.
*/

#include <WheatstoneBridge.h>

WheatstoneBridge wsb(A1, 365, 565, 0, 1000);

void setup()
{
  Serial.begin(9600);
  Serial.println("< Wheatstone Bridge Interface to Serial >");
  Serial.println("");
}

int val;
int valRaw;

void loop()
{
  val = wsb.measureForce();
  valRaw = wsb.getLastForceRawADC();
  Serial.print("Raw ADC value: ");
  Serial.println(valRaw, DEC);
  Serial.print("Calculated force: ");
  Serial.println(val, DEC);
  Serial.println("");
  delay(100);
}

/* Wheatstone Bridge Interface - Library */
