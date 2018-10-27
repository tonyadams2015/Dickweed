
#define PC_MAX_POWER 100
#define PC_MIN_POWER 0

int pc_sp = 0;

void pc_init (void)
{
  pc_sp = 0;
}

void pc_sp_check (void)
{
  if (pc_sp > PC_MAX_POWER)
  {
    pc_sp = PC_MAX_POWER;
  }
  else if (pc_sp < PC_MIN_POWER)
  {
    pc_sp = PC_MIN_POWER;
  }
}

void pc_set (int delta)
{
  pc_sp += delta;
  pc_sp_check ();
  bb_set (pc_sp);
  sm_event_send (POWER_CTRL_UPDATE, pc_sp);
}

int pc_get (void)
{
  return pc_sp;
}

void pc_start (void)
{
  bb_start ();
}

void pc_stop (void)
{
  bb_stop ();
}
