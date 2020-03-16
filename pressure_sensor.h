#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#define DELTA_R_MAX 200000
#define R_LOAD      1000000
#define V_I         1023
#define dVdt_THRESHOLD  12  /*12*/
#define ZERO_THRESH_MULT 2  /*2*/
#define REPEAT_STATES_CNT 3 /*3*/
#define REPEAT_STATES_MULT 2 /*2*/

#include "Arduino.h"

typedef struct press_state_t
{
    int state;
    unsigned int count;
}press_state_t;


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
    press_state_t     press_state[16];
    double  delta_r_max[16];
    
    
};

#endif
