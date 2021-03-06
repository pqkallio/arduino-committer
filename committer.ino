#include <Arduino.h>
#include "lcd/lcd.hpp"
#include "lcd/glyphs.hpp"
#include "pins/pins.hpp"
#include "button/button.hpp"
#include "temperature/temperature.hpp"
#include "mode/mode.hpp"
#include "led/led.hpp"
#include "date/date.hpp"
#include "mode/idlemode.hpp"
#include "mode/enterdatemode.hpp"
#include "mode/entertimemode.hpp"

#define TEMPERATURE_INTERVAL_MS 30000

// Hardware
LCDDisplay lcd;
RGBLed led(LED_RED, LED_GREEN, LED_BLUE);
ButtonStrip buttonStrip(BTN_IN);
TemperatureSensor temperatureSensor(TEMP_IN);

Date baseDate(2020, 10, 9, 0);

// Modes
ModeInterface* mode;
IdleMode idleMode(&lcd, &led, &buttonStrip, &temperatureSensor, TEMPERATURE_INTERVAL_MS);
EnterDateMode enterDateMode(&lcd, &led, &buttonStrip, &baseDate);
EnterTimeMode enterTimeMode(&lcd, &led, &buttonStrip, &baseDate);

void setup()
{
  Serial.begin(9600);

  enterDateMode.setNextMode(&enterTimeMode);
  enterTimeMode.setPreviousMode(&enterDateMode);
  enterTimeMode.setNextMode(&idleMode);

  mode = &enterDateMode;
  mode->onEnter();
}

void loop()
{
  unsigned long current_time = millis();

  ModeInterface* nextMode = mode->tick(current_time);

  if (mode != nextMode) {
    mode = nextMode;
    mode->onEnter();
  }

  delay(50);
}
