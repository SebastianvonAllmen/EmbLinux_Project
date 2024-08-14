/*
 * per_display.c
 * controll peripheral display over I2C
 * Author: Raphael Cargiet
 * License: PDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for sleep */

#include "McuI2cLib.h" /* I2C library */
#include "McuSSD1306.h" /* OLED SSD1306/SH1106 library */

/* graphics */
#include "McuGDisplaySSD1306.h" /* graphics library */

/* fonts */
#include "McuFontDisplay.h"
#include "McuFontHelv10Normal.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv18Bold.h"

static void init(void) {
  McuI2cLib_Init();
  McuSSD1306_Init();
}

static void demoGraphics(void) {
  McuGDisplaySSD1306_Clear();
  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawCircle(50, 30, 15, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_UpdateFull();
}

static void demoText(void) {
  McuSSD1306_Clear();
  McuSSD1306_PrintString(0, 0, (uint8_t*)"Hello\nWorld!");
  McuSSD1306_PrintString(3, 15, (uint8_t*)"The quick brown fox");
  McuSSD1306_PrintString(4, 15, (uint8_t*)"jumps over");
  McuSSD1306_PrintString(5, 15, (uint8_t*)"the lazy dog");
}

static void demoFont(void) {
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  int color = McuGDisplaySSD1306_COLOR_BLUE;

  McuGDisplaySSD1306_Clear();
  x = y = 0;
  McuFontDisplay_WriteString((unsigned char*)"hello\nworld!", color, &x, &y, font);
  McuGDisplaySSD1306_UpdateFull();
}

int main(void) {
  printf("OLED example in C\n");
  init();
  demoText();
  sleep(2);
  demoGraphics();
  sleep(2);
  demoFont();
  return 0;
}

