#define ENC_CLK_PIN 3 
#define ENC_DT_PIN 2
#define ENC_SW_PIN 1



ClickEncoder *encoder;
static int16_t enc_last, enc_value;

void enc_timerIsr()
{
  encoder->service();
}

void enc_init ()
{
 encoder = new ClickEncoder(ENC_DT_PIN, ENC_CLK_PIN, ENC_SW_PIN, 2);
 Timer1.initialize(1000);
 Timer1.attachInterrupt(enc_timerIsr); 
 enc_last = -1;
}

void enc_update (void)
{
  enc_value += encoder->getValue();
  
  if (enc_value != enc_last)
  {
    sm_event_send (ENC_UPDATE, enc_value - enc_last);
    enc_last = enc_value;
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
