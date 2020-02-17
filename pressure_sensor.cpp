#include "pressure_sensor.h"

pressure_sensor::pressure_sensor()
{
  //Serial.begin(9600);
  reset();
  
}
    
void pressure_sensor::re_callibrate()
{
  delay(1000);
  double V_o = 0;
  for(int i = 0; i < 16; i++)
  {
    V_o = 0;
    for(int j = 0; j < 100; j++)
    {
      delay(1);
      V_o += analogRead(i);
    }
    V_o = V_o/(double)100.0;
    if(V_o == 0)
    {
      r0[i]=0;
    }
    else
    {
      r0[i] = (double)R_LOAD*(  ( (double)V_I/V_o    )   - (double)1.0     );
    }
      
  }
  /*Serial.print("Start calib\n");
  for(int i = 0; i < 16; i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(r0[i]);
    Serial.print("\n");
      
  } 
  Serial.print("End calib\n");*/
}

void pressure_sensor::measure_resistance(int fiber_index)
{
    double V_o = 0;

    for(int i = 0; i < 10; i++)
    {
      V_o += analogRead(fiber_index);
    }
    V_o = V_o/(double)10.0;

    
    double r = (double)R_LOAD*(  ( (double)V_I/V_o    )   - (double)1.0     );
    delta_r[fiber_index] = (r0[fiber_index]-r)/(double)DELTA_R_MAX;
    if(delta_r[fiber_index] > 1.0  )
    {
      delta_r[fiber_index] = 1.0;
    }
    else if(delta_r[fiber_index] < 0)
    {
      delta_r[fiber_index] = 0;
    }
    /*
    Serial.print(fiber_index);
    Serial.print(" R0: ");
    Serial.print(r0[fiber_index]);
    Serial.print(" R: ");
    Serial.print(r);
    Serial.print(" delta r: " );
    Serial.print(delta_r[fiber_index]);
    Serial.print("\n");
    */
}

double pressure_sensor::get_delta_r(int fiber_index)
{
  if(fiber_index < 0 || fiber_index > 15)
  {
    return 0;  
  }
  return delta_r[fiber_index];  
}    

void pressure_sensor::reset()
{
  for(int i = 0; i < 16; i++)
  {
    delta_r[i]= 0;  
    r0[i] = 0;
  }  
  re_callibrate();
}
