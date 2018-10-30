
int menu [NUM_STATES] = {OFF, POWER_CTRL, TEMP_CTRL, THERM, DELAY_TIMER, MENU};
String menu_names [NUM_STATES] =  {"Off", "Power control", "Temp control", "Thermometer", "Delayed heat", "Menu"};
int menu_index = 0;

void ui_clear ()
{
  lcd.clear (); 
}

void ui_therm_print (int t)
{
  lcd.printField (0, 1, 3, round (t));
  lcd.print (" C");
}

void ui_off_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Off");
}

void ui_power_ctrl_sp_print (int power_ctrl_sp)
{
  lcd.printField (11, 0, 5, power_ctrl_sp);
  lcd.print ("%");
}

void ui_temp_ctrl_sp_print (int temp_ctrl_sp)
{
  lcd.printField (11, 0, 5, temp_ctrl_sp);
  lcd.print ("C");
}

void ui_bb_power_print (int p)
{
  lcd.printField (11, 1, 5, p);
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

void ui_delay_timer_lb_print (void)
{
  lcd.setCursor (0,0);
  lcd.print ("Delay timer:");  
}

void ui_delay_time_print (long t)
{
  long s_total = t / 1000;
  int h = s_total / 3600;
  int s_remaining = s_total % 3600;
  int m = s_remaining / 60;
  int s = s_remaining % 60;

  char buf[8];
  sprintf(buf,"%02d:%02d:%02d",h, m, s);
  lcd.printField (0, 1, 16, buf);
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
