#include <SimpleTimer.h>

SimpleTimer timer;

void setup (void)
{
  enc_init ();
  //enc_sw_init ();
  bb_init ();
  lcd_init ();
  pc_init ();
  therm_init ();
  sm_init ();
  timer.setInterval(1000, therm_update);
  timer.setInterval(100, enc_update);
  //timer.setInterval(100, enc_sw_update);

  therm_update ();
}

void loop (void)
{
  timer.run();
}
