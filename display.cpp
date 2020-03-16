#include "display.h"


lcd_display::lcd_display()
{
  tft = TFT_HX8357();
  tft.init();
  tft.setRotation(3);
  tft.setTextFont((int)0);
  reset();
  //Serial.begin(9600);
}
    
void lcd_display::update_display(int fiber_index, double state)
{
  if(fiber_index > 15 || fiber_index < 0)
  {
    return;  
  }

  //fibers[fiber_index] = (double)state/(double)FIBER_MAX_VAL;
  fibers[fiber_index] = state;
/*  Serial.print(fiber_index);
  Serial.print(" Raw val: ");
  Serial.print(state);
  Serial.print(" percent value: ");
  Serial.print(fibers[fiber_index]);
  Serial.print("\n");*/

  update_rectangles();
}

void lcd_display::print_calibrating()
{
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString((char*)"recalibrating", 240, 160, 4);


  
}
void lcd_display::reset()
{
  for(int i = 0; i<16; i++)
  {
    fibers[i] = 0;  
  }
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      rectangles[i][j] = 0;
      tft.fillRect(60*i, 40*j, 60, 40, TFT_BLUE);
  
    }  
  }

}

void lcd_display::reset_v3()
{
  for(int i = 0; i<16; i++)
  {
    fibers[i] = 0;  
  }
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
      rectangles[i][j] = 0;
      tft.fillRect(60*i, 40*j, 60, 40, TFT_BLACK);
  
    }  
  }

}



unsigned int lcd_display::get_rgb_color(double percent)
{
  
  if(percent > 1.0 || percent < 0.0)
  {
    percent = 1;  
  }
  unsigned int return_int = percent * 188;
  
  unsigned int return_rgb = 0;

/*  Serial.print("in rgb func. percent: ");
  Serial.print(percent);
  Serial.print(" return int: ");
  Serial.print(return_int);
  Serial.print("\n");
*/  
  if(return_int < 64)
  {
//    Serial.print("in 1 \n");
    return_rgb = 31 + (return_int<<5);
  }
  else if(return_int < 95)
  {
//    Serial.print("in 2 \n");
    return_rgb = (63<<5) + (94-return_int);
  }
  else if(return_int < 126)
  {
//    Serial.print("in 3 \n");
    return_rgb =  (63<<5) + ((return_int - 94)<<11) ;
  }
  else if(return_int < 189)
  {
//    Serial.print("in 4 \n");
    return_rgb = (31<<11) + ((188 - return_int)<<5);
  }
//  Serial.print(return_rgb, BIN);  
//  Serial.print("\n");  
  return return_rgb;
}



unsigned int lcd_display::get_rgb_color_v2(double percent)
{
  
  if(percent > 1.0 || percent < 0.0)
  {
    percent = 1;  
  }
  
  int dec_resolution = 3*percent;
  double new_percent = (double)dec_resolution/(double)3;
  
  unsigned int return_int = new_percent * 188;
  
  unsigned int return_rgb = 0;

/*  Serial.print("in rgb func. percent: ");
  Serial.print(percent);
  Serial.print(" return int: ");
  Serial.print(return_int);
  Serial.print("\n");
*/  
  if(return_int < 64)
  {
//    Serial.print("in 1 \n");
    return_rgb = 31 + (return_int<<5);
  }
  else if(return_int < 95)
  {
//    Serial.print("in 2 \n");
    return_rgb = (63<<5) + (94-return_int);
  }
  else if(return_int < 126)
  {
//    Serial.print("in 3 \n");
    return_rgb =  (63<<5) + ((return_int - 94)<<11) ;
  }
  else if(return_int < 189)
  {
//    Serial.print("in 4 \n");
    return_rgb = (31<<11) + ((188 - return_int)<<5);
  }
//  Serial.print(return_rgb, BIN);  
//  Serial.print("\n");  
  return return_rgb;
}


unsigned int lcd_display::get_rgb_color_v3(double percent)
{
  
  if(percent > 1.0 || percent < 0.0)
  {
    percent = 1;  
  }
  int dec_resolution = 8*percent;
  double new_percent = (double)dec_resolution/(double)8;
  unsigned int return_rgb = 31*new_percent;

  return return_rgb;
}

unsigned int lcd_display::get_rgb_color_v4(double percent)
{
  
  if(percent > 1.0 || percent < 0.0)
  {
    percent = 1;  
  }
  unsigned int return_rgb = 0;
  if(percent < 0.5)
  {
    return_rgb = get_rgb_color((double)0);
  }
  else if(percent < .7)
  {
    return_rgb = get_rgb_color((double).5);
  }
  else
  {
    return_rgb = get_rgb_color((double)1.0);
  }
  
  return return_rgb;
}

void lcd_display::update_rectangles()
{
  unsigned int rgb_col = get_rgb_color(0.0);
  double percent = 0;
  for(int i = 0; i<8; i++)
  {
    for(int j = 0; j<8; j++)
    {
        if(fibers[i] !=0.0 && fibers[j+8] != 0.0)
        {
          //percent = (double)2L*(fibers[i]*fibers[j+8])/(fibers[i]+fibers[j+8]);
          percent = (fibers[i]*fibers[j+8]);
              
        }
        else
        {
          percent = 0;
        }
      rgb_col = get_rgb_color_v4(   percent);
      //rgb_col = get_rgb_color_v3(   percent);
/*      Serial.print(i);
      Serial.print(" , ");
      Serial.print(j);
      Serial.print(": ");
      Serial.print(fibers[i]);
      Serial.print(" , ");
      Serial.print(fibers[j+8]);
      Serial.print(": ");
      Serial.print("Percent: ");
      Serial.print(percent);
      Serial.print(" R:");
      Serial.print((rgb_col>>11) & int(31));
      Serial.print(" G:");
      Serial.print((rgb_col>>5) & int(63));
      Serial.print(" B:");
      Serial.print((rgb_col) & int(31));
      Serial.print("\n");
*/
      if(rectangles[i][j] != rgb_col)
      {
        rectangles[i][j] = rgb_col;
        tft.fillRect(60*i, 40*j, 60, 40, rgb_col);
        
      } 
    }  
  }   
}





  
