#include "pressure_sensor.h"

pressure_sensor::pressure_sensor()
{
  //Serial.begin(9600);
  //vertical 
  delta_r_max[0] = 110000;//400000;
  delta_r_max[1] = 620000;
  delta_r_max[2] = 52000;//520000;
  delta_r_max[3] = 430000;
  delta_r_max[4] = 55000;//250000;
  delta_r_max[5] = 200000;
  delta_r_max[6] = 200000;
  delta_r_max[7] = 200000;
  //horizontal 
  delta_r_max[8] = 200000;
  delta_r_max[9] = 200000;
  delta_r_max[10] = 22000; //110000;
  delta_r_max[11] = 15000; //81000;
  delta_r_max[12] = 1400;  //41000;
  delta_r_max[13] = 200000;
  delta_r_max[14] = 200000;
  delta_r_max[15] = 200000;

  //reset();
  
}
    
void pressure_sensor::re_callibrate()
{
  Serial.print("start calibrate\n");
  delay(5000);
  double V_o = 0;
  for(int i = 0; i < 16; i++)
  {
    V_o = 0;
    dVdt[i] = 0;
    press_state[i].state=0;
    for(int j = 0; j < 100; j++)
    {
      delay(2);
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
  Serial.print("end calibration\n");

}

void pressure_sensor::measure_resistance(int fiber_index)
{
    
    if(fiber_index < 0 || fiber_index > 15)
    {
      return;  
    }
    
    double V_o = 0;

    for(int i = 0; i < 10; i++)
    {
      V_o += analogRead(fiber_index);
    }
    V_o = V_o/(double)10.0;
    dVdt[fiber_index] = V_o - dVdt[fiber_index];    
    
    double r = (double)R_LOAD*(  ( (double)V_I/V_o    )   - (double)1.0     );
    delta_r[fiber_index] = (r0[fiber_index]-r)/(double)delta_r_max[fiber_index];
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
    press_state[i].state = 0;
    press_state[i].count = 0;
  }  
  re_callibrate();
}

bool pressure_sensor::release_detect()
{
  for(int i = 0; i < 16; i++)
  {
    int dVdt_value = 0;
    
    if(dVdt[i]> dVdt_THRESHOLD)
    {
      dVdt_value = 1;
    }
    else if(dVdt[i] < -dVdt_THRESHOLD)\
    {
      dVdt_value = -1;
    }
    else
    {
      dVdt_value = 0;
    }

    if(press_state[i].state == 2 && (dVdt[i] >= -ZERO_THRESH_MULT*dVdt_THRESHOLD) &&   (dVdt[i] <= ZERO_THRESH_MULT*dVdt_THRESHOLD) )
    {  
      dVdt_value = 0;
    }
    
    switch(press_state[i].state)
    {
      case 0:
      {
        if(dVdt_value == -1)
        {
          press_state[i].count++;
          if(press_state[i].count > REPEAT_STATES_CNT)
          {
            press_state[i].state = 1;
            press_state[i].count = 1;
          }
        }
        else if (dVdt_value ==  1)
        {
          press_state[i].state = 0;
          press_state[i].count = 1;
        }
        break;
      }
      case 1:
      {
        if(dVdt_value ==  1)
        {
          press_state[i].count++;
          if(press_state[i].count > REPEAT_STATES_CNT)
          {
            press_state[i].state = 2;
            press_state[i].count = 1;
          }
        }
        /*else if (dVdt_value ==  -1)
        {
          press_state[i].state = 0;
          press_state[i].count = 1;
        }*/       
        break;
      }
      case 2:
      {
        if(dVdt_value == 0)
        {
          press_state[i].count++;
          if(press_state[i].count > REPEAT_STATES_MULT*REPEAT_STATES_CNT)
          {
            press_state[i].state = 3;
            press_state[i].count = 1;
          }          
        }
        else if(dVdt_value == -1)
        {
          press_state[i].state = 0;
          press_state[i].count = 1;
        }        
        break;
      }
      case 3:
      {
        press_state[i].state = 0;  
        break;
      }                
      default:
      {
        press_state[i].state = 0; 
        break;
      }     
    }
    if(press_state[i].state == 3)
    {
      Serial.print("release detected on fiber: ");
      Serial.print(i);
      Serial.print("\n");
      return true;
    }
  }
 
  /*for(int i = 0; i < 16; i++)
  {
      Serial.print("|");
      Serial.print(i);
      Serial.print(":");
      Serial.print(press_state[i].state);
      Serial.print(":");
      Serial.print(press_state[i].count);          
   }
   Serial.print("\n");*/
   return false;
}
