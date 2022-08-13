#include <SPI.h>
#include <SE0352NQ01.h>
#include "Ap_29demo.h"
// Include fonts from https://github.com/adafruit/Adafruit-GFX-Library/tree/master/Fonts
#include "FreeSansBold12pt7b.h"
#include "FreeSerifBoldItalic24pt7b.h"
// See README.md for Chinese fonts
#include "CJK14pt.h"
#include "CJK16ptB.h"

unsigned char frame[10800];
SE0352NQ01 SE0352;

void textDemo() {
  Serial.print("Text Demo 1/2");
  memset(frame, PIC_WHITE, 10800);
  Serial.println("ASCII");
  // Will wrap around
  SE0352.drawString((char*)"Landscape 0", 300, 30, FreeSansBold12pt7b, 0, frame);
  SE0352.drawString((char*)"Kongduino", 60, 125, FreeSerifBoldItalic24pt7b, 0, frame);
  SE0352.drawString((char*)"Landscape 2", 10, 30, FreeSansBold12pt7b, 2, frame);
  SE0352.drawString((char*)"Portrait 1", 90, 20, FreeSansBold12pt7b, 1, frame);
  SE0352.drawString((char*)"Portrait 3", 10, 20, FreeSansBold12pt7b, 3, frame);
  uint16_t zhongwenyekeyi[] = {0x4e2d, 0x6587, 0x4E5F, 0x53EF, 0x4EE5}; // 中文也可以
  Serial.write('.');
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 200, CJK14ptfont, CJK14ptsparse, CJK14ptSparseLen, CJK14ptHeight, 0, frame);
  Serial.write('.');
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 160, CJK16ptBfont, CJK16ptBsparse, CJK16ptBSparseLen, CJK16ptBHeight, 0, frame);
  Serial.write('.');
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 45, CJK14ptfont, CJK14ptsparse, CJK14ptSparseLen, CJK14ptHeight, 2, frame);
  Serial.write('.');
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 65, CJK16ptBfont, CJK16ptBsparse, CJK16ptBSparseLen, CJK16ptBHeight, 2, frame);
  SE0352.send(frame);
  Serial.println(" done!");
  delay(2000);

  Serial.print("Text Demo 2/2");
  memset(frame, PIC_WHITE, 10800);
  uint16_t px = 2, py = 2;
  Serial.write('.');
  SE0352.drawBitmap(gThermometer_width, gThermometer_height, px, py, 0, 0, 0, frame, gThermometer, 0);
  // In FreeSansBold12pt7b, ` has been replaced with an o, with a bigger yOffset, to make a ° sign cheaply :-)
  Serial.write('.');
  SE0352.drawString((char*)"27`", px + gThermometer_width + 5, (py + gThermometer_height) / 2 + 12, FreeSansBold12pt7b, 0, frame);
  py += gThermometer_height + 10;
  Serial.write('.');
  SE0352.drawBitmap(gHumidity_width, gHumidity_height, px, py, 0, 0, 0, frame, gHumidity, 0);
  Serial.write('.');
  SE0352.drawString((char*)"58%", px + gHumidity_width + 5, (py + gHumidity_height) / 1.2, FreeSansBold12pt7b, 0, frame);

  uint16_t x = 120;
  for (uint16_t y = 0; y < 237; y += 3) {
    SE0352.plotLine(x, y, 359, y + 10, frame, 0);
    x += 5;
  }
  SE0352.drawCircle(60, 189, 50, frame, 0);
  for (x = 0; x < 100; x += 2) SE0352.plotVLine(120 + x, 139, 239, frame, 0);
  for (uint16_t y = 139; y < 239; y += 2) SE0352.plotHLine(229, y, 349, frame, 0);
  SE0352.send(frame);
  Serial.println(" done!");
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("EPD TEST");
}

void loop() {
  unsigned int i;
  SE0352.fill(PIC_WHITE);
  delay(1000);
  Serial.println("gImage_1");
  SE0352.send(gImage_1);
  delay(1000);
  Serial.println("gImage_Kongduino");
  SE0352.send(gImage_Kongduino);
  delay(1000);
  Serial.println("textDemo");
  textDemo();
  delay(15000);
}
