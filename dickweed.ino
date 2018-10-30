#include <MsTimer2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <SimpleTimer.h>

enum events {STATE_CHANGE = 1, CLICK, DOUBLE_CLICKED, ENC_UPDATE, THERM_UPDATE, POWER_CTRL_UPDATE, TEMP_CTRL_UPDATE, BB_UPDATE, SELECT_NEW_STATE, DT_TICK, DT_EXPIRED};
enum states {OFF, POWER_CTRL, TEMP_CTRL, THERM, MENU, DELAY_TIMER, NUM_STATES};

void sm_event_send (int, long);

SimpleTimer timer;
