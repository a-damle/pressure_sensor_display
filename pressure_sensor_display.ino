
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
    if(sensors.release_detect())
    {
      the_display.print_calibrating();
      sensors.re_callibrate();
      the_display.reset();
      //the_display.reset_v3();  
    }
    the_display.update_display(i, sensors.get_delta_r(i));
  }

  for(int i = 8; i < 13; i++)
  {
    sensors.measure_resistance(i);
    //Serial.print(i);
    //Serial.print(" delta r : ");
    //Serial.print(sensors.get_delta_r(i));
    //Serial.print("\n");
    if(sensors.release_detect())
    {
      the_display.print_calibrating();
      sensors.re_callibrate();
      the_display.reset();      
      //the_display.reset_v3();  
    }  
    the_display.update_display(i, sensors.get_delta_r(i));
  }

}
