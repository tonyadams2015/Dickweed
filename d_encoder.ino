#define ENC_CLK_PIN 3 
#define ENC_DT_PIN 2
#define ENC_SW_PIN 1

#include <ClickEncoder.h>
#include <TimerOne.h>

ClickEncoder *encoder;
int16_t last, value;

void timerIsr()
{
  encoder->service();
}

void enc_init ()
{
 encoder = new ClickEncoder(ENC_DT_PIN, ENC_CLK_PIN, ENC_SW_PIN, 2);
 Timer1.initialize(1000);
 Timer1.attachInterrupt(timerIsr); 
 last = -1;
}

void enc_update (void)
{
  value += encoder->getValue();
  
  if (value != last)
  {
    sm_event_send (ENC_UPDATE, value - last);
    last = value;
  }

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) 
  {
    switch (b) 
    {
    case ClickEncoder::DoubleClicked:
      sm_event_send (LONG_PRESS, 0);
      break;    
    case ClickEncoder::Clicked:
      sm_event_send (CLICK, 0);
      break;    
    }
  }
}
