
#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float therm_old_t = 0;
bool therm_enabled = false;
int therm_timer_id = -1;

void therm_init (void)
{
  sensors.begin();
  therm_enabled = false;
}

void therm_enable (bool enable)
{
  therm_enabled = enable;

  if (enable)
  {
    if (therm_timer_id == -1)
    {
      therm_timer_id = timer.setInterval(1000, therm_update);
    }
  }
  else
  {
    if (therm_timer_id != -1)
    {
      timer.deleteTimer (therm_timer_id);
      therm_timer_id = -1;
    }
  }
  
}

void therm_update ()
{
  float t;
  sensors.requestTemperatures();
  t = sensors.getTempCByIndex(0);
  therm_old_t = t;
  sm_event_send (THERM_UPDATE, t);
}
