#include "display.h"


lcd_display::lcd_display()
{
  tft = TFT_HX8357();
  tft.init();
  tft.setRotation(3);
  tft.setTextFont((int)0);
  reset();
}
    
void lcd_display::update_display(int fiber_index, double percent)
{
  if(fiber_index > 15 || fiber_index < 0)
  {
    return;  
  }
  fibers_percent[fiber_index] = percent;
  //update_fibers();
  update_circles();
}

void lcd_display::update_fibers()
{
  unsigned int rgb_col = get_rgb_color(0.0);
  double percent = 0;
   
  for(int line = 0; line < 16; line ++)
  {
    //vertical lines
    if(line < 8)
    {
      if(get_rgb_color(fibers_percent[line]) != lines[line])
      {
          lines[line] = get_rgb_color(fibers_percent[line]);
          tft.drawFastVLine((line+1)*53, 0, 320, lines[line]);
          for(int j =0; j < 8; j++)
          {
            tft.fillCircle((line+1)*53, (j+1)*35, 10, circles[line][j]);
          }
      }  
    }
    else //horizontal lines 
    {
      if(get_rgb_color(fibers_percent[line]) != lines[line])
      {
          lines[line] = get_rgb_color(fibers_percent[line]);
          tft.drawFastHLine(0, 35*(line-7), 480, lines[line]);
          for(int i =0; i < 8; i++)
          {
            tft.fillCircle((i+1)*53, (line-7)*35, 10, circles[i][line-8]);
          } 

      }  
    }
  }
}

void lcd_display::update_circles()
{
  double percent = 0;
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      if(fibers_percent[i] == 0 || fibers_percent[j+8] ==0)
      {
        percent = 0;
      }
      else
      {
        percent =( ( fibers_percent[i] + fibers_percent[j+8] ) /2);
      }
      if( get_rgb_color(percent) != circles[i][j])
      {
          circles[i][j] = get_rgb_color(percent);
          tft.fillCircle((i+1)*53, (j+1)*35, 10, circles[i][j]);
      } 
     } 
   }     

}

void lcd_display::reset()
{
  tft.fillScreen(TFT_BLACK);
  for(int i = 0; i<16; i++)
  {
    fibers_percent[i] = 0;
    lines[i] = 0;  
  }
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      circles[i][j] = 0;
    } 
  }
  update_fibers();
  update_circles();
}

unsigned int lcd_display::get_rgb_color(double percent)
{
  
  if(percent > 1.0 || percent < 0.0)
  {
    percent = 1;  
  }
  unsigned int return_int = percent * 188;
  
  unsigned int return_rgb = 0;
 
  if(return_int < 64)
  {
    return_rgb = 31 + (return_int<<5);
  }
  else if(return_int < 95)
  {
    return_rgb = (63<<5) + (94-return_int);
  }
  else if(return_int < 126)
  {
    return_rgb =  (63<<5) + ((return_int - 94)<<11) ;
  }
  else if(return_int < 189)
  {
    return_rgb = (31<<11) + ((188 - return_int)<<5);
  } 
  return return_rgb;
}


  
