
static int menu [NUM_STATES] = {OFF, POWER_CTRL, TEMP_CTRL, THERM, MENU};
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
    menu_index = 0;
  }
  else if (menu_index < 0)
  {
    menu_index = NUM_STATES - 1
    ;
  }
}

void ui_menu_update ()
{
  lcd.clear ();
  lcd.setCursor (0,0);
  switch (menu[menu_index])
  {
  case OFF:
    lcd.print ("-> Off");
    lcd.setCursor (0,1);
    lcd.print ("   Power control");
    break;
  case POWER_CTRL:
    lcd.print ("-> Power control");
    lcd.setCursor (0,1);
    lcd.print ("   Temp control");
    break;
  case TEMP_CTRL:
    lcd.print ("-> Temp control");
    lcd.setCursor (0,1);
    lcd.print ("   Thermometer");
    break;
  case THERM :
    lcd.print ("-> Thermometer");
    lcd.setCursor (0,1);
    lcd.print ("   Menu");
    break; 
  case MENU:
    lcd.print ("-> Menu");
    lcd.setCursor (0,1);
    lcd.print ("   Off");
    break;
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
