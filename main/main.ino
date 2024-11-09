#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_TEMP A7
#define PIN_POT A6

#define PIN_GATE 3
#define PIN_LED_HEAT 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

int16_t temp_table(0);
int16_t temp_ref(0);

void setup() 
{
  lcd.init();
  lcd.backlight();

  pinMode(PIN_GATE, OUTPUT);
  pinMode(PIN_LED_HEAT, OUTPUT);

  lcd.setCursor(0, 1);
  lcd.print("Set");

  lcd.setCursor(8, 1);
  lcd.print("Temp");
}

void loop() 
{
  static uint32_t timer_1 = 0;
  if(millis() - timer_1 >= 500)
  {
    timer_1 = millis();

    temp_table = 110 * ( float( analogRead(PIN_TEMP) ) / 1023.0 * 5.0 ) - 273;
    temp_ref = 50 + analogRead(PIN_POT) * 50 / 1023;

    if(temp_table < temp_ref)
    {
      digitalWrite(PIN_GATE, 1);
      digitalWrite(PIN_LED_HEAT, 1);

      lcd.setCursor(4, 0);
      lcd.print("HEATING+");
    }
    else
    {
      digitalWrite(PIN_GATE, 0);
      digitalWrite(PIN_LED_HEAT, 0);

      lcd.setCursor(4, 0);
      lcd.print("COOLING-");
    }
    
    lcd.setCursor(3, 1);
    lcd.print("    ");
    lcd.setCursor(3, 1);
    lcd.print(temp_ref);
    lcd.print( char(223) );

    lcd.setCursor(12, 1);
    lcd.print("    ");
    lcd.setCursor(12, 1);
    lcd.print(temp_table);
    lcd.print( char(223) );
  }

  static uint8_t ctr = 0;
  static uint32_t timer_2 = 0;
  if(millis() - timer_2 >= 200)
  {
    timer_2 = millis();
    switch(ctr)
    {
      case 0: 
        lcd.setCursor(0, 0);
        lcd.print("    ");
        lcd.setCursor(12, 0);
        lcd.print("    ");
        break;
      case 1:
        lcd.setCursor(3, 0);
        lcd.print( char(255) );
        lcd.setCursor(12, 0);
        lcd.print( char(255) );
        break;
      case 2:
        lcd.setCursor(2, 0);
        lcd.print( char(255) );
        lcd.setCursor(13, 0);
        lcd.print( char(255) );
        break;
      case 3:
        lcd.setCursor(1, 0);
        lcd.print( char(255) );
        lcd.setCursor(14, 0);
        lcd.print( char(255) );
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print( char(255) );
        lcd.setCursor(15, 0);
        lcd.print( char(255) );
        break;
    }
    ctr++;
    if(ctr > 4) ctr = 0;
  }
}