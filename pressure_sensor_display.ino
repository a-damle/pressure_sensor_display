
#include "display.h"
#include "pressure_sensor.h"
void setup() 
{
    Serial.begin(115200);

}

void loop() 
{
  static lcd_display the_display;
  static pressure_sensor sensors;

  for(int i = 0; i < 16; i++)
  {
    //remove if statement for full display 
    if(i==0 || i==1 || i==2 || i==8 || i==9)
    {
      sensors.measure(i);  
      the_display.update_display(i, sensors.get_percent(i));
      Serial.print("|");
      Serial.print(i);
      Serial.print(":");
      Serial.print(sensors.get_voltage(i));
      Serial.print(":");
      Serial.print(sensors.get_percent(i));      
      Serial.print("| \t");
    }
  }
  Serial.print("\n");

}
