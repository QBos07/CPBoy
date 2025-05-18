#pragma once

#include <sdk/calc/calc.h>
#include "../core/preferences.h"

#define XSTR(x)           STR(x)
#define STR(x)            #x

#define CPBOY_VERSION     "v0.3.1"

#define CAS_LCD_WIDTH     ::width
#define CAS_LCD_HEIGHT    ::height 

#define MAX_FILENAME_LEN  200

#define MCS_DIRECTORY     "CPBoy"

#define DIRECTORY_MAIN     "\\fls0\\CPBoy\\"
#define DIRECTORY_ROM      DIRECTORY_MAIN "roms"

#define EXTENSION_ROM     ".gb"

#define TOGGLE(value) ((value) = !(value))

#define RGB555_TO_RGB565(rgb555) ( \
	0 | \
	((rgb555 & 0b0111110000000000) <<1) | \
	((rgb555 & 0b0000001111100000) <<1) | \
	(rgb555 & 0b0000000000011111) \
)

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
