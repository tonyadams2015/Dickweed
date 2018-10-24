
LiquidCrystal_I2C lcd(0x27,20,4);

void lcd_init ()
{
  lcd.init();
  lcd.backlight();
}
