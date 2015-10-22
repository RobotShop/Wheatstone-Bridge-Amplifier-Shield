// Include the Wheatstone library
#include <WheatstoneBridge.h>

// Include the LCD library
#include <LiquidCrystal.h>

// Declare external global lcd
extern LiquidCrystal lcd;

// Button 
#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   4
#define btnLEFT   8
#define btnSELECT 16
#define btnNONE   32

// Return the first pressed button found
byte read_LCD_buttons();

// Return the number of digits in an integer
byte countDigits(int);

// Display full screen of text (2 rows x 16 characters)
void displayScreen(char[], char[]);

// Display to wait for select and then do so
void waitSelect(bool);

int getValueADC(char[], char[], byte, byte, byte);

int getValueInRange(char[], char[], byte, int, int, int, int, int);
