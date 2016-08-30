/* Wheatstone Bridge Interface - Library */

/*
	This library was created by Sébastien Parent-Charette for RobotShop.
	It is meant to be used with the RB-Onl-38 from RobotShop.
	This product is available here: http://www.robotshop.com/en/strain-gauge-load-cell-amplifier-shield-2ch.html
	This library may work with other WheatStone bridge interface boards that use an analog pin for input.
	
	Changes history:
	2016-08-29
	v1.10-19
	Added example for 2 shield / 4 load cells.
	
	2016-07-28
	v1.10-16
	Changed output to be on one line.
	Corrected default init of strain1 to be 1000 (instead of 750).

	2016-04-21
	v1.10-08
	Added reading and display of both load cells to the basic example.
	
	2015-10-08
	v1.0
	First release of the library. Basic functionality is available.
*/

#include <WheatstoneBridge.h>

WheatstoneBridge wsb_strain1(A0, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain2(A1, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain3(A2, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain4(A3, 365, 675, 0, 1000);

void setup()
{
  Serial.begin(9600);
  Serial.println("< Wheatstone Bridge (double shield) Interface to Serial >");
}

int val1;
int valRaw1;
int val2;
int valRaw2;
int val3;
int valRaw3;
int val4;
int valRaw4;

void loop()
{
  // Read strain 1
  val1 = wsb_strain1.measureForce();
  valRaw1 = wsb_strain1.getLastForceRawADC();
  
  // Read strain 2
  val2 = wsb_strain2.measureForce();
  valRaw2 = wsb_strain2.getLastForceRawADC();
  
  // Read strain 3
  val3 = wsb_strain3.measureForce();
  valRaw3 = wsb_strain3.getLastForceRawADC();
  
  // Read strain 4
  val4 = wsb_strain4.measureForce();
  valRaw4 = wsb_strain4.getLastForceRawADC();
  
  // Display header line
  Serial.println("");
  Serial.println("\t\t\tStrain 1\tStrain 2\tStrain 3\tStrain 4");
  
  // Display raw ADC values
  Serial.print("Raw ADC values:\t\t");
  Serial.print(valRaw1, DEC); Serial.print("\t\t");
  Serial.print(valRaw2, DEC); Serial.print("\t\t");
  Serial.print(valRaw3, DEC); Serial.print("\t\t");
  Serial.println(valRaw4, DEC);
  
  // Display calculated force
  Serial.print("Calculated force:\t");
  Serial.print(val1, DEC); Serial.print("\t\t");
  Serial.print(val2, DEC); Serial.print("\t\t");
  Serial.print(val3, DEC); Serial.print("\t\t");
  Serial.println(val4, DEC);
  
  // Delay for readability
  delay(1000);
}

/* Wheatstone Bridge Interface - Library */
