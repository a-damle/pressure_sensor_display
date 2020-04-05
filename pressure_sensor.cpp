#include "pressure_sensor.h"

pressure_sensor::pressure_sensor()
{
  //initialize max voltages here 
  max_voltage[0] = 36;
  max_voltage[1] = 15;//40
  max_voltage[2] = 15;//30
  max_voltage[3] = 1;
  max_voltage[4] = 1;
  max_voltage[5] = 1;
  max_voltage[6] = 1;
  max_voltage[7] = 1;
  max_voltage[8] = 200;
  max_voltage[9] = 206;
  max_voltage[10] = 1;
  max_voltage[11] = 1;
  max_voltage[12] = 1;
  max_voltage[13] = 1;
  max_voltage[14] = 1;
  max_voltage[15] = 1;
  max_voltage[16] = 1;
  max_voltage[17] = 1;
          
  reset();
  
}
    

void pressure_sensor::measure(int fiber_index)
{
    
    if(fiber_index < 0 || fiber_index > 15)
    {
      return;  
    }
    
    double V_o = 0;

    for(int i = 0; i < 10; i++)
    {
      delay(1);
      V_o += analogRead(fiber_index);
    }
    V_o = V_o/(double)10.0; 
    
    voltage[fiber_index] = V_o;
    percent_of_max_voltage[fiber_index] = (V_o - base_voltage[fiber_index])/max_voltage[fiber_index];
    
}

void pressure_sensor::reset()
{
  for(int i = 0; i < 16; i++)
  {
    voltage[i] = 0;
    base_voltage[i] = 0;
    percent_of_max_voltage[i] = 0;
  }
  calibrate();  

}



int pressure_sensor::get_voltage(int fiber_index)
{
  if(fiber_index < 0 || fiber_index > 15)
  {
    return 0;  
  }  
  return voltage[fiber_index];
}

double pressure_sensor::get_percent(int fiber_index)
{
  if(fiber_index < 0 || fiber_index > 15)
  {
    return 0;  
  }  

  if(percent_of_max_voltage[fiber_index] < .35)
  {
    return .0;
  }
  else if(percent_of_max_voltage[fiber_index] < .50)
  {
    return .50;    
  }
  else if(percent_of_max_voltage[fiber_index] < .65)
  {
    return .65;
  }
  else if(percent_of_max_voltage[fiber_index] < .80)
  {
    return .8;
  }
  else
  {
    return 1.0;
  }
  return 0;
}


void pressure_sensor::calibrate()
{
    
    Serial.print("start calibrate\n");
    for(int j = 0; j < 16; j++)
    {
      double V_o = 0;
      for(int i = 0; i < 100; i++)
      {
        delay(1);
        V_o += analogRead(j);
      }
      V_o = V_o/(double)100.0; 
      base_voltage[j] = V_o;
    }
    Serial.print("end calibrate\n");
}
