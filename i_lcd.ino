
class DwLcd : public LiquidCrystal_I2C {

public:
  
  using LiquidCrystal_I2C::LiquidCrystal_I2C;
  void clearChars (int col, int line, int num);
  void printField (int col, int line, int num, int int_to_print);  
};

void DwLcd::clearChars (int col, int line, int num)
{
  LiquidCrystal_I2C::setCursor (col, line);

  for (int i = 0; i < num; i++)
  {
    LiquidCrystal_I2C::print (" ");
  }

  LiquidCrystal_I2C::setCursor (col, line);
}

void DwLcd::printField (int col, int line, int num, int int_to_print)
{
  DwLcd::clearChars (col, line, num);
  LiquidCrystal_I2C::print (int_to_print);
}

DwLcd lcd(0x27,20,4);

void lcd_init ()
{
  lcd.init();
  lcd.backlight();
}
