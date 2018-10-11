
#define MAX_TEMP 95
#define MIN_TEMP 0 

int tc_lookup_power_level (void);

int tc_sp = 0;
int tc_curr_temp = 0;

void tc_init (void)
{
  tc_sp = 0;
}

void tc_sp_check (void)
{
  if (tc_sp > MAX_TEMP)
  {
    tc_sp = MAX_TEMP;
  }
  else if (tc_sp < MIN_TEMP)
  {
    tc_sp = MIN_TEMP;
  }
}

void tc_set (int delta)
{
  int p;
  tc_sp += delta;
  tc_sp_check ();
  p = tc_lookup_power_level ();
  bb_set (p);
  sm_event_send (TEMP_CTRL_UPDATE, tc_sp);
}

void tc_set_measured_temp (int t)
{
  int p;
  tc_curr_temp = t;
  p = tc_lookup_power_level ();
  bb_set (p);
}

void tc_start (void)
{
  bb_start ();
}

void tc_stop (void)
{
  bb_stop ();
}

int tc_lookup_power_level (void)
{
  int t_error = tc_sp - tc_curr_temp;
  int power = 0;
  if (t_error > 0)
  {
    if (t_error > 7)
    {
      power = 100;
    }
    else if (t_error > 4)
    {
      power = 50;
    }
    else if (t_error > 1)
    {
      power = 25;
    }
  }

  return power;
}
