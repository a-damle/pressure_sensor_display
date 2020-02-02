
#include "display.h"

//#include <TFT_HX8357.h> // Hardware-specific library

//TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library


void setup() {
  randomSeed(analogRead(0));
}

void loop() {
  static lcd_display the_display;
  static bool state = false;

  state = !state;
  the_display.update_display(random(0, 15), state);
  delay(10);

}
