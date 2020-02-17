
#include "display.h"
#include "pressure_sensor.h"
void setup() {
  randomSeed(analogRead(0));
    Serial.begin(9600);

}

void loop() {
  static lcd_display the_display;
  static pressure_sensor sensors;
  
  int analog_reading = 0;


  for(int i = 0; i < 5; i++)
  {
    sensors.measure_resistance(i);
    //Serial.print(i);
    //Serial.print(" delta r : ");
    //Serial.print(sensors.get_delta_r(i));
    //Serial.print("\n");
    the_display.update_display(i, sensors.get_delta_r(i));
  }

  for(int i = 8; i < 13; i++)
  {
    sensors.measure_resistance(i);
    //Serial.print(i);
    //Serial.print(" delta r : ");
    //Serial.print(sensors.get_delta_r(i));
    //Serial.print("\n");  
    the_display.update_display(i, sensors.get_delta_r(i));
  }

  //sensors.re_callibrate();
  /*for(int i = 0; i < 16; i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(sensors[i].get_delta_r(i));
    Serial.print("\t");  
  }

  Serial.print("\n");*/
/*
  for(int i = 0; i < 4; i++)
  {
    analog_reading = analogRead(i);
    the_display.update_display(i, analog_reading); 
  }

  for(int i = 8; i < 12; i++)
  {
    analog_reading = analogRead(i);
    the_display.update_display(i, analog_reading); 
  }
*/
}
