#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#define DELTA_R_MAX 200000
#define R_LOAD      1000000
#define V_I         1023
#define dVdt_THRESHOLD  25
#define ZERO_THRESH_MULT 3

#include "Arduino.h"


class pressure_sensor
{
  public:
            pressure_sensor();
    
    void    re_callibrate();

    void    measure_resistance(int fiber_index);
    
    void    reset();
    double  get_delta_r(int fiber_index);
    bool    release_detect();
  private:
  
    double  delta_r[16];
    double  dVdt[16];
    double  r0[16];
    int     press_state[16];
    
    
};

#endif
