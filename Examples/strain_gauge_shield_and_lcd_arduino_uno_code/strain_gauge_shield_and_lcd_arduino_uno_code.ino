/* Wheatstone Bridge Interface - Arduino Load Cell & LCD example */

/*
	This library was created by Sébastien Parent-Charette for RobotShop.
	It is meant to be used with the RB-Onl-38 and RB-Ite-161 from RobotShop.
	These products are available here:
          http://www.robotshop.com/en/strain-gauge-load-cell-amplifier-shield-2ch.html
          http://www.robotshop.com/en/16x2-lcd-shield-kit-arduino.html
          http://www.robotshop.com/en/arduino-r3-stackable-headers.html
	This library may work with other WheatStone bridge interface boards that use an analog pin for input and other LCD screens.
	
	Changes history:
	2015-10-22
	v1.0
	First release of the example. Linear 2 point calibration is possible. Once calibrated, it constantly displays the raw ADC value & measured force.
        All output on the screen is also double over the serial port for easy debugging purposes.
*/

// Include the Wheatstone library
#include <WheatstoneBridge.h>

// Include the LCD library
#include <LiquidCrystal.h>

// Include support function header
#include "strain_gauge_shield_and_lcd_support_functions.h"

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Initial calibration values
const int CST_STRAIN_IN_MIN = 350;       // Raw value calibration lower point
const int CST_STRAIN_IN_MAX = 650;       // Raw value calibration upper point
const int CST_STRAIN_OUT_MIN = 0;        // Weight calibration lower point
const int CST_STRAIN_OUT_MAX = 1000;     // Weight calibration upper point

const int CST_CAL_FORCE_MIN = 0;
const int CST_CAL_FORCE_MAX = 32000;
const int CST_CAL_FORCE_STEP = 50;
const int CST_CAL_FORCE_STEP_LARGE = 500;

// Initialize the Wheatstone bridge object
WheatstoneBridge wsb(A1, CST_STRAIN_IN_MIN, CST_STRAIN_IN_MAX, CST_STRAIN_OUT_MIN, CST_STRAIN_OUT_MAX);

// < Setup function >
void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize LCD screen
  lcd.begin(16, 2);
  
  // Intro screen
  displayScreen("RobotShop   v1.0", "Wheatstone Bridg");
  Serial.println("RobotShop v1.0 Wheatstone Bridge");
  delay(2500);
  
  // Up/down screen
  displayScreen("Press up/dn/l/r", "to change values");
  Serial.println("Press up/down/left/right to change values");
  delay(2500);
  
  // Select screen
  displayScreen("Press select to", "complete a step");
  Serial.println("Press select to complete a step");
  delay(2500);
  
  // Calibration - linear interpolation
  int cal_adc_low = CST_STRAIN_IN_MIN;
  int cal_adc_high = CST_STRAIN_IN_MAX;
  int cal_force_low = CST_STRAIN_OUT_MIN;
  int cal_force_high = CST_STRAIN_OUT_MAX;
  
  // Calibration - Low value
  displayScreen("* Calibration *", "Low value");
  Serial.println("* Calibration * - Low value");
  delay(2500);
  // Get force value
  cal_force_low = getValueInRange("Set low force", "Force:", 7, cal_force_low, CST_CAL_FORCE_MIN, CST_CAL_FORCE_MAX, CST_CAL_FORCE_STEP, CST_CAL_FORCE_STEP_LARGE);
  // Get ADC raw value
  cal_adc_low = getValueADC("Set low raw ADC", "Raw ADC:", 9, A1, btnSELECT);
  
  // Calibration - High value
  displayScreen("* Calibration *", "High value");
  Serial.println("* Calibration * - High value");
  delay(2500);
  // Get force value
  cal_force_high = getValueInRange("Set high force", "Force:", 7, cal_force_high, CST_CAL_FORCE_MIN, CST_CAL_FORCE_MAX, CST_CAL_FORCE_STEP, CST_CAL_FORCE_STEP_LARGE);
  // Get ADC raw value
  cal_adc_high = getValueADC("Set high raw ADC", "Raw ADC:", 9, A1, btnSELECT);
  
  // Perform calibration
  Serial.println("Wheatstone Bridge calibration:");
  Serial.print("> iMin = "); Serial.println(cal_adc_low);
  Serial.print("> iMax = "); Serial.println(cal_adc_high); 
  Serial.print("> oMin = "); Serial.println(cal_force_low); 
  Serial.print("> oMax = "); Serial.println(cal_force_high); 
  wsb.linearCalibration(cal_adc_low, cal_adc_high, cal_force_low, cal_force_high);
  
  // Setup display labels
  displayScreen("[A1]:", "Force:");
}

// Timing management
long display_time_step = 1000;
long display_time = 0;

// Force measurement & display
int strain_adc;
int strain_force;
int force_pos_offset;

// < Main code >
void loop()
{
  // Check if it is time to make a new measurement / update the display
  if(millis() > (display_time_step + display_time))
  {
    // Make a force measurement and obtain the calibrated force value
    strain_force = wsb.measureForce();
    
    // Obtain the raw ADC value from the last measurement
    strain_adc = wsb.getLastForceRawADC();
    
    // Calculate force position offset (right-aligned text)
    force_pos_offset = (4 - countDigits(strain_force));
    if(strain_force <= 0)
      force_pos_offset -= 1;
    
    // Display raw ADC value
    lcd.setCursor(12, 0); lcd.print("       ");
    lcd.setCursor(12, 0); lcd.print(strain_adc);
    Serial.print("[A1], raw ADC: ");
    Serial.println(strain_adc, DEC);
    
    // Display force value
    lcd.setCursor(11, 1);
    lcd.print("     ");
    lcd.setCursor((11 + force_pos_offset), 1);
    lcd.print(strain_force);
    Serial.print("[A1], force: ");
    Serial.println(strain_force, DEC);
    Serial.println("");
    
    // Reset time counter
    display_time = millis();
  }
}
