#pragma once

#include <stdint.h>
#include "controls.h"
#include "preferences.h"
#include "palettes.h"

#define FRAMESKIP_MIN 1
#define FRAMESKIP_MAX 100

void set_frameskip(struct gb_s *gb, bool enabled, uint8_t amount);

void set_interlacing(struct gb_s *gb, bool enabled);

uint8_t execute_rom(struct gb_s *gb);

uint8_t prepare_emulator(struct gb_s *gb, emu_preferences *preferences);

uint8_t close_rom(struct gb_s *gb);

void free_emulator(struct gb_s *gb);

uint8_t run_emulator(struct gb_s *gb, emu_preferences *prefs);

uint8_t load_rom(emu_preferences *prefs);