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

#ifndef RS_WHEATSTONE_BRIDGE_INTERFACE
#define RS_WHEATSTONE_BRIDGE_INTERFACE

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class WheatstoneBridge
{
	public:
		WheatstoneBridge(byte AnalogPin, int inputMin = 0, int inputMax = 1023, int outputMin = 0, int outputMax = 65535);
		~WheatstoneBridge();
		int measureForce();
		int getLastForce();
		int getLastForceRawADC();
		void linearCalibration(int inputMin = 0, int inputMax = 1023, int outputMin = 0, int outputMax = 65535);
	
	private:
	// < Local attributes >
		// Hardware
		byte iPin = A1;			// Defaults to "Strain 2"
		
		// Calibration
		int iMin = 0;
		int iMax = 1023;
		int oMin = 0;
		int oMax = 65535;
		
		// Measurements
		int lastForceADCRaw = 0;
		int lastForce = 0;
};

#endif

/* Wheatstone Bridge Interface - Library */