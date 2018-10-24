
#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

static float old_t = 0;

void therm_init (void)
{
  sensors.begin();
}

void therm_update ()
{
  float t;
  sensors.requestTemperatures();
  t = sensors.getTempCByIndex(0);
  old_t = t;
  sm_event_send (THERM_UPDATE, t);
}
