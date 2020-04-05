#include <TFT_HX8357.h>
#include <User_Setup.h>


#ifndef DISPLAY_H
#define DISPLAY_H

#define FIBER_MAX_VAL 1023L

#include <TFT_HX8357.h> 
#include "Arduino.h"

//this class handles the LCD display. lines represent the fibers and circles represent intersection between two fibers. the circles turn from blue to red with increasing pressure   
class lcd_display
{
  public:
    //constructor 
    lcd_display();

    //update display based on percent change in a fiber
    void update_display(int fiber_index, double percent);

    //reset display 
    void reset();
  
  private:
    //tft class from library TFT_HX8357
    TFT_HX8357 tft;

    //stores percent change of fibers 
    double fibers_percent[16];

    //stores color of lines 
    unsigned int lines[16];

    //stores color of circles 
    unsigned int circles[8][8];

    //convert percent to rgb color 
    unsigned int get_rgb_color(double percent);

    //update color of circles 
    void update_circles();

    //update color of lines
    void update_fibers(); 
};

#endif
