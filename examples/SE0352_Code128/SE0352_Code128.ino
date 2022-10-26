uint8_t frame[10800];

#include <SPI.h>
#include <SE0352NQ01.h>
#include "Wisblock.h"

void setup() {
  memset(frame, PIC_WHITE, 10800);
  SE0352.fillScreen(PIC_WHITE);
  SE0352.refresh();
  delay(100);
  SE0352.drawBitmap(Wisblock_s_width, Wisblock_s_height, 359 - Wisblock_s_width, 0, frame, gPartial_Wisblock_s, 0);
  SE0352.send(frame);
  SE0352.refresh();
  SE0352.makeCode128((char *)"Kongduino", 2, 60, 20, 40, 0, frame);
  SE0352.makeCode128((char *)"WisBLOCK", 2, 60, 80, 140, 0, frame);
  SE0352.send(frame);
  SE0352.refresh();
}

void loop() {
}
