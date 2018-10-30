
#define BB_PERIOD 4000
#define BB_OUTPUT_PIN1 10
#define BB_OUTPUT_PIN2 11
#define BB_OUTPUT_PIN3 12
#define BB_OUTPUT_PIN4 13

int bb_on_time = 0;
int bb_off_time = 0;
boolean bb_enable = false;

void bb_pin_ctrl (boolean state);

void bb_init (void)
{
  bb_enable = false;
  pinMode(BB_OUTPUT_PIN1, OUTPUT);
  pinMode(BB_OUTPUT_PIN2, OUTPUT);
  pinMode(BB_OUTPUT_PIN3, OUTPUT);
  pinMode(BB_OUTPUT_PIN4, OUTPUT);
  bb_pin_ctrl (LOW);
}

void bb_set (int power)
{
  bb_on_time = BB_PERIOD * power / 100;
  bb_off_time = BB_PERIOD - bb_on_time;
  sm_event_send (BB_UPDATE, power);
  if (bb_enable == true)
  {
    bb_start ();
  }
}

void bb_turn_on (void)
{
  MsTimer2::stop();
  if (bb_on_time == BB_PERIOD)
  {
    bb_pin_ctrl (HIGH);
  }
  else
  {
    bb_pin_ctrl (HIGH);
    MsTimer2::set (bb_on_time, bb_turn_off);
    MsTimer2::start();
  }
}

void bb_turn_off (void)
{
  MsTimer2::stop();
  if (bb_off_time == BB_PERIOD)
  {
    bb_pin_ctrl (LOW);
  }
  else
  {
    bb_pin_ctrl (LOW);
    MsTimer2::set (bb_off_time, bb_turn_on);
    MsTimer2::start();
  }
}

void bb_start (void)
{
  bb_enable = true;
  bb_turn_on ();
}

void bb_restart ()
{
  if (bb_enable == true)
  {
    bb_turn_on ();
  }
}

void bb_stop (void)
{
  bb_enable = false;
  MsTimer2::stop();
  bb_pin_ctrl (LOW);
}

void bb_pin_ctrl (boolean state)
{
  digitalWrite(BB_OUTPUT_PIN1, state);
  digitalWrite(BB_OUTPUT_PIN2, state);
  digitalWrite(BB_OUTPUT_PIN3, state);
  digitalWrite(BB_OUTPUT_PIN4, state);
}
