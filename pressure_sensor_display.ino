
#include "display.h"

void setup() {
  randomSeed(analogRead(0));
    Serial.begin(9600);

}

void loop() {
  static lcd_display the_display;
  static bool state = false;
  int num1 = random(0,7);
  int num2 = random(8,15);
  int analog_reading = 0;

  for(int i = 0; i < 4; i++)
  {
    analog_reading = analogRead(i);
    the_display.update_display(i, (analog_reading > 500)); 
  }

  for(int i = 8; i < 12; i++)
  {
    analog_reading = analogRead(i);
    the_display.update_display(i, (analog_reading > 500)); 
  }

}
