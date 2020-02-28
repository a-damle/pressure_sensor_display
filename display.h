
#ifndef DISPLAY_H
#define DISPLAY_H

#define FIBER_MAX_VAL 1023L

#include <TFT_HX8357.h> 
#include "Arduino.h"


class lcd_display
{
  public:
    lcd_display();
    
    void update_display(int fiber_index, double state);
    void reset();
    void reset_v3();
    void print_calibrating();
  
  private:
    
    TFT_HX8357 tft;
    
    double fibers[16];
    unsigned int rectangles[8][8];
    unsigned int get_rgb_color(double percent);
    unsigned int get_rgb_color_v2(double percent);
    unsigned int get_rgb_color_v3(double percent);
    void update_rectangles();
    
};

#endif
