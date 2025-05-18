#include "functions.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sdk/os/file.h>

char_const16_t *char_to_char_const16(char_const16_t *wstr, const char *str)
{
  char_const16_t *dest = wstr;

  for (const char *c = str; *c; c++, dest++)
  {
    *dest = *c;
  }

  *dest = '\0';

  return wstr;
}

char *char_const16_to_char(char *str, const char_const16_t *wstr)
{
  char *dest = str;

  for (const char_const16_t *c = wstr; *c; c++, dest++)
  {
    *dest = *c;
  }

  *dest = '\0';

  return str;
}

uint32_t align_val(uint32_t val, uint32_t at)
{
  if ((val % at) == 0) 
  {
    return val;
  }

  return val + (at - (val % at));
}

char *itoa_leading_zeros(uint32_t val, char *str, uint8_t base, uint8_t digits)
{
  uint32_t tmp = val / base;
  uint8_t digit_count = 1;

  char *p = str;

  while (tmp != 0)
  {
    tmp /= base;
    digit_count++;
  }

  for (uint8_t i = 0; i < (digits - digit_count); i++, p++)
  {
    *p = '0';
  }

  itoa(val, p, base);

  return str;
}
