
#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_HX8357.h> 
#include "Arduino.h"

class lcd_display
{
  public:
    lcd_display();
    
    void update_display(int line, bool state);
    void reset();
  
  private:
    
    TFT_HX8357 tft;
    
    bool lines[16];
    bool points[16][16];

    void place_circles();
    
};

#endif
