// Include support function header
#include "strain_gauge_shield_and_lcd_support_functions.h"

// Return the first pressed button found
byte read_LCD_buttons()
{
  // read the value from the sensor 
  int adc_key_in = analogRead(A5);
  
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 250)  return btnUP; 
  if (adc_key_in < 450)  return btnDOWN; 
  if (adc_key_in < 650)  return btnLEFT; 
  if (adc_key_in < 850)  return btnSELECT;  
  
  return btnNONE;                // when all others fail, return this.
}

// Return the number of digits in an integer
byte countDigits(int num)
{
  byte count=0;
  while(num)
  {
    num = num / 10;
    count += 1;
  }
  return count;
}

// Display full screen of text (2 rows x 16 characters)
void displayScreen(char row1[], char row2[])
{
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(row1);
  lcd.setCursor(0,1); lcd.print(row2);
  Serial.println(""); Serial.println(row1); Serial.println(row2);
}

// Display to wait for select and then do so
void waitSelect(bool disp = false)
{
  if(disp)
  {
    lcd.setCursor(0,1); lcd.print("< press select >");
    Serial.println("< press select >");
  }
  while(read_LCD_buttons() != btnSELECT){};
}

// Displays text on screen and an ADC value at chosen position from selected pin. Waits for user input (select button by default)
int getValueADC(char row1[], char row2[], byte pos, byte pin, byte endButton)
{
  int value = 0;
  int lastValue = -1;
  byte buttons = btnNONE;
  
  displayScreen(row1, row2);
  delay(1500);
  while(buttons != endButton)
  {
    // Check inputs
    buttons = read_LCD_buttons();
    
    // Update readout from analog port
    value = analogRead(pin);
    
    // Update display
    if(value != lastValue)
    {
      lcd.setCursor(pos, 1); lcd.print("                ");
      lcd.setCursor(pos, 1); lcd.print(value);
      Serial.println(""); Serial.println(row1); Serial.print(row2); Serial.print(" "); Serial.println(value);
      lastValue = value;
      delay(350);
    }
  };
  
  // Return the last measured ADC value
  return (value);
}

// Displays text on screen and a changeable value at chosen position. User input can change the value (left/right/up/down) and press select to accept it.
int getValueInRange(char row1[], char row2[], byte pos, int valueDefault, int valueMin, int valueMax, int valueStep, int valueStepLarge)
{
  int value = valueDefault;
  int lastValue = -1;
  int buttons = btnNONE;
  
  displayScreen(row1, row2);
  delay(1500);
  while(buttons != btnSELECT)
  {
    // Check inputs
    buttons = read_LCD_buttons();
    switch(buttons)
    {
      case btnUP:
        value += valueStep;
        if(value > valueMax)
          value = valueMax;
        break;
        
      case btnRIGHT:
        value += valueStepLarge;
        if(value > valueMax)
          value = valueMax;
        break;

      case btnDOWN:
        value -= valueStep;
        if(value < valueMin)
          value = valueMin;
        break;

      case btnLEFT:
        value -= valueStepLarge;
        if(value < valueMin)
          value = valueMin;
        break;
    }
    
    // Update display
    if(value != lastValue)
    {
      lcd.setCursor(pos, 1); lcd.print("                ");
      lcd.setCursor(pos, 1); lcd.print(value);
      Serial.println(""); Serial.println(row1); Serial.print(row2); Serial.print(" "); Serial.println(value);
      lastValue = value;
      delay(350);
    }
  };
  
  // Return the last selected value
  return (value);
}
