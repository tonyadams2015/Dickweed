
static int curr_state = OFF;

void sm_enter_off (void);
void sm_enter_power_ctrl (void);
void sm_enter_temp_ctrl (void);
void sm_enter_menu (void);

void sm_off (int, int);
void sm_power_ctrl (int, int);
void sm_temp_ctrl (int, int);
void sm_menu (int, int);

void (*sm_enter_cb [NUM_STATES])(void) = {sm_enter_off,
                                          sm_enter_power_ctrl,
                                          sm_enter_temp_ctrl,
                                          sm_enter_menu};

void (*sm_cb [NUM_STATES])(int, int) =   {sm_off,
                                          sm_power_ctrl,
                                          sm_temp_ctrl,
                                          sm_menu};
                                          
void sm_init (void)
{
  sm_next_state (TEMP_CTRL);
}

void sm_event_send (int event, int value)
{
  sm_update (event, value);
}

int sm_get_curr_state (void)
{
  return curr_state;
}

void sm_next_state (int new_state)
{
  curr_state = new_state;
  sm_enter ();
}

void sm_enter (void)
{
  ui_clear ();
  sm_enter_cb [curr_state] ();
}

void sm_update (int event, int value)
{
  if (event == LONG_PRESS)
  {
    sm_next_state (MENU);
    return;
  }
  else if (event == CLICK)
  {
    // The encoder switch code uses the same timer as bang bang
    // so restart after a click.
    bb_restart ();
  }
  
  sm_cb [curr_state] (event, value);
}

void sm_enter_off (void)
{
  ui_off_print ();
  pc_stop ();
  tc_stop ();
}

void sm_enter_power_ctrl (void)
{
  ui_power_ctrl_lb_print ();
  pc_start ();
}

void sm_enter_temp_ctrl (void)
{
  ui_temp_ctrl_lb_print ();
  tc_start ();
}

void sm_off (int event, int value)
{
}

void sm_power_ctrl (int event, int value)
{
  switch (event)
  {
  case THERM_UPDATE:
    ui_therm_print (value);
    break;
  case ENC_UPDATE:
    pc_set (value);
    break;
  case POWER_CTRL_UPDATE:
    ui_power_ctrl_sp_print (value);
    break;
  }
}

void sm_temp_ctrl (int event, int value)
{
  switch (event)
  {
  case TEMP_CTRL_UPDATE:
    ui_temp_ctrl_sp_print (value);
    break;
  case BB_UPDATE:
    ui_bb_power_print (value);
    break;
  case THERM_UPDATE:
    ui_therm_print (value);
    tc_set_measured_temp (value);
    break;
  case ENC_UPDATE:
    tc_set (value);
    break;
  }
}

void sm_enter_menu (void)
{
  tc_stop ();
  pc_stop ();
  ui_menu_init ();
}

void sm_menu (int event, int value)
{
  switch (event)
  {
  case ENC_UPDATE:
    ui_menu_scroll (value);
    break;
  case CLICK:
    ui_menu_select ();
    break;
  case SELECT_NEW_STATE:
    sm_next_state (value);
    break;
  }
}
