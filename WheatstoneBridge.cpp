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

#include "WheatstoneBridge.h"

// < Constructor >
/* Sets the proper analog pin to input. Also does calibration if given by user.
*/
WheatstoneBridge::WheatstoneBridge(byte AnalogPin, int inputMin, int inputMax, int outputMin, int outputMax)
{
	iPin = AnalogPin;
	pinMode(iPin, INPUT);
	iMin = inputMin;
	iMax = inputMax;
	oMin = outputMin;
	oMax = outputMax;
}

// < Destructor >
WheatstoneBridge::~WheatstoneBridge()
{
	// Nothing to destruct
}

// measureForce
/* Obtain the analog measurement from ADC and convert it by interpolation to a force using the latest calibration values.
*/
int WheatstoneBridge::measureForce()
{
	// Obtain ADC raw measurement
	lastForceADCRaw = analogRead(iPin);
	
	// 
	lastForce = map(lastForceADCRaw, iMin, iMax, oMin, oMax) + oMin;
	
	// Return value
	return (lastForce);
}

// getLastForce
/* Return the last force calculation (does not perform a new reading).
*/
int WheatstoneBridge::getLastForce()
{
	return (lastForce);
}

// getLastForceRawADC
/* Return the last force raw ADC value (does not perform a new reading).
*/
int WheatstoneBridge::getLastForceRawADC()
{
	return (lastForceADCRaw);
}

// linearCalibration
/* Calibrates the Wheatstone bridge linear interpolation.
	inputMin:	Minimum expected value of raw ADC input
	inputMax:	Maximum expected value of raw ADC output
	outputMin:	First (lower) calibration point with a known force, usually 0.
	outputMax:	Second (higher) calibration point with a known force, usually near the maximum force measurable by the load cell used.
*/
void WheatstoneBridge::linearCalibration(int inputMin, int inputMax, int outputMin, int outputMax)
{
	iMin = inputMin;
	iMax = inputMax;
	oMin = outputMin;
	oMax = outputMax;
}

/* Wheatstone Bridge Interface - Library */