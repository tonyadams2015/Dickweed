
#define DT_UPDATE_TIME 1000
#define DT_HRS_TO_MS 3600000

// delay time in ms
long dt_delay_time = 0;
int dt_timer_id = -1;

void dt_start (void)
{
  if (dt_timer_id == -1)
  {
    dt_timer_id = timer.setInterval(DT_UPDATE_TIME, dt_update);
  }
}

void dt_stop (void)
{
  timer.deleteTimer (dt_timer_id);
  dt_timer_id = -1;
  dt_delay_time = 0;
}

void dt_set (int h)
{
  dt_delay_time += h * DT_HRS_TO_MS;
  if (dt_delay_time < 0)
  {
    dt_delay_time = 0;
  }
  sm_event_send (DT_TICK, dt_delay_time);
}

void dt_update (void)
{
  dt_delay_time -= DT_UPDATE_TIME;
  sm_event_send (DT_TICK, dt_delay_time);
  if (dt_delay_time <= 0)
  {
    sm_event_send (DT_EXPIRED, 0);
  }
}
