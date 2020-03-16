
#include "display.h"
#include "pressure_sensor.h"
void setup() {
  randomSeed(analogRead(0));
    Serial.begin(115200);

}

void loop() {
  static lcd_display the_display;
  static pressure_sensor sensors;
  static bool first_run = true;

  if(first_run)
  {
    the_display.print_calibrating();
    sensors.reset();
    first_run = false;  
  }
  int analog_reading = 0;


  for(int i = 0; i < 5; i++)
  {
    delay(10);
    if(i!=1 && i!=3)
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

  for(int i = 8; i < 13; i++)
  {
    delay(10);
    if(i!=8 && i!=9)
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

}
