#include <SPI.h>
#include <SE0352NQ01.h>
#include "CJK16ptB.h"
#include "Wisblock.h"

uint8_t frame[10800];

void setup() {
  memset(frame, PIC_WHITE, 10800);
  SE0352.fillScreen(PIC_WHITE);
  SE0352.refresh();
  delay(100);
  SE0352.drawBitmap(Wisblock_s_width, Wisblock_s_height, 359 - Wisblock_s_width, 0, frame, gPartial_Wisblock_s, 0);
  SE0352.send(frame);
  SE0352.refresh();
  delay(1000);

  Serial.println("partialRefresh 0");
  SE0352.fillCircle(200, 100, 30, 0, frame);
  uint16_t zhongwenyekeyi[] = {0x4e2d, 0x6587, 0x4E5F, 0x53EF, 0x4EE5}; // 中文也可以
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 20, CJK16ptBfont, CJK16ptBsparse, CJK16ptBSparseLen, CJK16ptBHeight, 0, frame);
  SE0352.drawUnicode(zhongwenyekeyi, 5, 40, 123, CJK16ptBfont, CJK16ptBsparse, CJK16ptBSparseLen, CJK16ptBHeight, 0, frame);
  for (uint8_t z = 0; z < 5; z++) {
    digitalWrite(PIN_LED2, HIGH);
    SE0352.partialRefresh(40 + z * 16, 16, 40 + z * 16 + 15, 39, 0, frame);
    delay(100);
    digitalWrite(PIN_LED2, LOW);
  }
  SE0352.partialRefresh(40, 123, 120, 139, 0, frame);
  Serial.println("partialRefresh 1");
  SE0352.partialRefresh(170, 70, 229, 129, 0, frame);

  Serial.println("partialRefresh 2");
  for (uint8_t orn = 0; orn < 4; orn ++) {
    SE0352.drawBitmap(Wisblock_s_width, Wisblock_s_height, (SE0352.width(orn) - 1) - Wisblock_s_width, 0, frame, gPartial_Wisblock_s, orn);
    SE0352.partialRefresh((SE0352.width(orn) - 1) - Wisblock_s_width, 0, (SE0352.width(orn) - 1), Wisblock_s_height, orn, frame);
  }
}

void loop() {
}
