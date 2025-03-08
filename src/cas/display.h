#pragma once

#include <stdint.h>

#define SCREEN_DATA_REGISTER ((volatile uint32_t *)0xB4000000)

inline void prepare_gb_lcd() 
{
  // ((void(*)(int, int, int, int))0x80038068)(0, CAS_LCD_WIDTH - 1, 0, (LCD_HEIGHT * 2) - 1);
  ((void(*)(int, int, int, int))0x80038a10)(0, CAS_LCD_WIDTH - 1, 0, (LCD_HEIGHT * 2) - 1);
  // ((void(*)(int))0x80038040)(0x2c);
  ((void(*)(int))0x800389e8)(0x2c);
}
