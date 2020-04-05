#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#define R_LOAD      1000000
#define V_I         1023

#include "Arduino.h"



//this class reads the analog pins and stores the voltage as a percent of a maximum voltage
class pressure_sensor
{
  public:
    //constructor 
            pressure_sensor();
    
    //measure voltage of analog pin and compute % of voltage under max pressure 
    void    measure(int fiber_index);
    
    //reset stored values and recalibrate     
    void    reset();

    //output voltage of analog pin
    int     get_voltage(int fiber_index);

    //output % of voltage under max pressure 
    double  get_percent(int fiber_index);

    //calibrate base voltage values 
    void    calibrate();
  
  private:

    //stores voltages of analog pins 
    int     voltage[16];

    //stores base voltages of analog pins. recalibrated automatically 
    int     base_voltage[16];

    //stores max voltages. must be calibrated manually 
    int     max_voltage[16];

    //stores % of max voltage
    double  percent_of_max_voltage[16];
};

#endif
