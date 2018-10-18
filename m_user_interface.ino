
static int menu [NUM_STATES] = {OFF, POWER_CTRL, TEMP_CTRL, THERM, MENU};
String menu_names [NUM_STATES] =  {"Off", "Power control", "Temp control", "Thermometer", "Menu"};
static int menu_index = 0;

void ui_clear ()
{
  lcd.clear (); 
}

void ui_therm_print (int t)
{
  lcd.setCursor (0,1);
  lcd.print ("     ");
  lcd.setCursor (0,1);
  lcd.print (round(t));
  lcd.print (" C");
}

void ui_off_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Off");
}

void ui_power_ctrl_sp_print (int power_ctrl_sp)
{
  lcd.setCursor (11,0);
  lcd.print ("     ");
  lcd.setCursor (11,0);
  lcd.print (power_ctrl_sp);
  lcd.print ("%");
}

void ui_temp_ctrl_sp_print (int temp_ctrl_sp)
{
  lcd.setCursor (11,0);
  lcd.print ("     ");
  lcd.setCursor (11,0);
  lcd.print (temp_ctrl_sp);
  lcd.print ("C");
}

void ui_bb_power_print (int p)
{
  lcd.setCursor (11,1);
  lcd.print ("     ");
  lcd.setCursor (11,1);
  lcd.print (p);
  lcd.print ("%");
}

void ui_power_ctrl_lb_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Set power:");
}

void ui_temp_ctrl_lb_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Set temp:");
}

void ui_therm_lb_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Thermometer:");  
}

void ui_menu_init (void)
{
  menu_index = 0;
  ui_menu_update ();
}

void ui_menu_index_check ()
{
  if (menu_index >= NUM_STATES)
  {
    menu_index = MENU;
  }
  else if (menu_index < 0)
  {
    menu_index = OFF;
  }
}

void ui_menu_update ()
{
  String line_1 = String ("-> " + menu_names [menu_index]);
  String line_2;
  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print (line_1);
  if (menu_index < NUM_STATES)
  { 
    line_2 = String ("   " + menu_names [menu_index + 1]);
    lcd.setCursor (0,1);
    lcd.print (line_2);
  }    
}

void ui_menu_scroll (int delta)
{
  menu_index += (delta > 0)? 1:-1;
  ui_menu_index_check ();
  ui_menu_update ();
}

void ui_menu_select ()
{
  sm_event_send (SELECT_NEW_STATE, menu[menu_index]);
}
