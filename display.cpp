#include "display.h"


lcd_display::lcd_display()
{
  tft = TFT_HX8357();
  tft.init();
  tft.setRotation(1);
  reset();
}
    
void lcd_display::update_display(int line, bool state)
{
  if(line > 15 || line < 0)
  {
    return;  
  }


  //vertical lines

  if(line < 8)
  {
    if(lines[line] != state)
    {
      lines[line] = state;
        if(state)
        {
          tft.drawFastVLine((line+1)*53, 0, 320, TFT_RED);
        }
        else
        {
          tft.drawFastVLine((line+1)*53, 0, 320, TFT_GREEN);
        }
    }  
  }
  else //horizontal lines 
  {
    if(lines[line] != state)
    {
      lines[line] = state;
        if(state)
        {
          tft.drawFastHLine(0, 35*(line-7), 480, TFT_RED); 
        }
        else
        {
          tft.drawFastHLine(0, 35*(line-7), 480, TFT_GREEN); 
        }
    }  
  }

  place_circles();
}

void lcd_display::reset()
{
  for(int i = 0; i<16; i++)
  {
    lines[i] = false;  
  }
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      points[i][j] = false;  
    }  
  }  
  tft.fillScreen(TFT_BLACK);
  for(int16_t xpos = 53; xpos <= 470; xpos+= 53 )
  {
      tft.drawFastVLine(xpos, 0, 320, TFT_GREEN);    
  }
  
  for(int16_t ypos = 35; ypos <= 300; ypos+= 35 )
  {
      tft.drawFastHLine(0, ypos, 480, TFT_GREEN);    
  }
}


void lcd_display::place_circles()
{
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      if(lines[i]&&lines[j+8])
      {
         if(!points[i][j])
         {
          points[i][j] = true;
          tft.fillCircle((i+1)*53, (j+1)*35, 10, TFT_RED);
         } 
      }
      else
      {
        if(points[i][j])
        {
          points[i][j] = false;
          tft.fillCircle((i+1)*53, (j+1)*35, 10, TFT_BLACK);
          if(lines[i])
          {
            tft.drawFastVLine((i+1)*53, 0, 320, TFT_RED);
          }
          else
          {
            tft.drawFastVLine((i+1)*53, 0, 320, TFT_GREEN);
          }

          if(lines[j+8])
          {
            tft.drawFastHLine(0, (j+1)*35, 480, TFT_RED);
          }
          else
          {
            tft.drawFastHLine(0, (j+1)*35, 480, TFT_GREEN);
          }
        }
      } 
    }  
  }   
  
}


  
